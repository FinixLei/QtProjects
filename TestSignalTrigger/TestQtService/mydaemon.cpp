#include <QDebug>
#include <QProcess>

#include "mydaemon.h"

#ifdef Q_OS_WIN

#include <Windows.h>
#include <WinBase.h>
#include <WtsApi32.h>
#include <UserEnv.h>
#include <tchar.h>

BOOL launchGUIApplication(std::wstring app, std::vector<std::wstring>params)
{
    BOOL bResult = FALSE;

    DWORD dwSessionId = WTSGetActiveConsoleSessionId();
    if (dwSessionId == 0xFFFFFFFF)
    {
        return FALSE;
    }

    HANDLE hUserToken = NULL;
    if (WTSQueryUserToken(dwSessionId, &hUserToken) == FALSE)
    {
        return FALSE;
    }

    HANDLE hTheToken = NULL;
    if (DuplicateTokenEx(hUserToken, TOKEN_ASSIGN_PRIMARY | TOKEN_ALL_ACCESS, 0, SecurityImpersonation, TokenPrimary, &hTheToken) == TRUE)
    {

        if (ImpersonateLoggedOnUser(hTheToken) == TRUE)
        {
            DWORD dwCreationFlags = HIGH_PRIORITY_CLASS | CREATE_NEW_CONSOLE;

            STARTUPINFO si = { sizeof(si) };
            PROCESS_INFORMATION pi;
            SECURITY_ATTRIBUTES Security1 = { sizeof(Security1) };
            SECURITY_ATTRIBUTES Security2 = { sizeof(Security2) };

            LPVOID pEnv = NULL;
            if (CreateEnvironmentBlock(&pEnv, hTheToken, TRUE) == TRUE)
            {
                dwCreationFlags |= CREATE_UNICODE_ENVIRONMENT;
            }

            TCHAR path[MAX_PATH];
            _tcscpy_s(path, MAX_PATH, app.c_str());
            // _tcscpy_s(path, MAX_PATH, L"C:\\CameraWorkTool\\release\\FortisDesktopContainer.exe");

            TCHAR commandLine[MAX_PATH];
            // _tcscpy_s(commandLine, MAX_PATH, L"C:\\CameraWorkTool\\release\\FortisDesktopContainer.exe --app_id=F821976C-02E9-4835-99E2-5D32704EF4D4");
            _tcscpy_s(commandLine, MAX_PATH, L" ");
            for (auto item : params) {
                _tcscat_s(commandLine, MAX_PATH, item.c_str());
            }

            // Launch the process in the client's logon session.
            bResult = CreateProcessAsUser(
                hTheToken,
                (LPWSTR)(path),
                (LPWSTR)(commandLine),
                &Security1,
                &Security2,
                FALSE,
                dwCreationFlags,
                pEnv,
                NULL,
                &si,
                &pi
                );

            RevertToSelf();

            if (pEnv)
            {
                DestroyEnvironmentBlock(pEnv);
            }
        }
        CloseHandle(hTheToken);
    }
    CloseHandle(hUserToken);

    return bResult;
}

#endif


MyDaemon::MyDaemon()
{
    m_one = new PluginOne;
    m_two = new PluginTwo;

    QObject::connect(m_one, &PluginOne::dataChanged, m_two, &PluginTwo::writeFile);
    QObject::connect(m_one, &PluginOne::dataChanged, this, &MyDaemon::startProcess);
}

MyDaemon::~MyDaemon(){}

void MyDaemon::run() {
    qDebug() << "Starting......";
    int i = 100;
    while (i++ < 103) {
        m_one->setData(i);
    }
}

void MyDaemon::pause() {
    qDebug() << "Paused......";
}

void MyDaemon::resume() {
    qDebug() << "Resuming......";
}

void MyDaemon::startProcess() {
    qDebug() << "Start Process......";

    /*
    QStringList parameters;
    parameters << "1.txt";

    // Do not use "system()" or "QProcess::execute()" or "QProcess.start()"
    // This is because they will suspend the execution of the service.
    QProcess::startDetached("notepad.exe", parameters);
    */

    #ifdef Q_OS_WIN
        std::wstring app = L"notepad.exe";
        std::vector<std::wstring> params = {};
        if (launchGUIApplication(app, params) == FALSE) {
            qDebug() << "Failed to launch " << app.c_str();
        }
    #endif
}
