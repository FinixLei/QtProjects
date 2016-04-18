#include "mydaemon.h"
#include <QDebug>

#ifdef Q_OS_WIN
#include <Windows.h>
#include <WtsApi32.h>
#include <WinBase.h>
#endif

#ifdef Q_OS_WIN

BOOL CreateMyProcess(LPWSTR fullPath)
{
    HANDLE hTokenDup = NULL;

    ULONG sessionId = WTSGetActiveConsoleSessionId();
    if (!WTSQueryUserToken(sessionId, &hTokenDup))
    {
        DWORD error = GetLastError();
        qDebug() << "Last Error = " << error;
        return FALSE;
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);
    si.lpDesktop = NULL; // L"WinSta0\\Default";

    qDebug() << "Before CreateProcessAsUser()";

    LPVOID pEnv = NULL;
    BOOL createResult = CreateProcessAsUser(hTokenDup, NULL, fullPath, NULL, NULL, FALSE,
        NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE, pEnv, NULL, &si, &pi);

    qDebug() << "Done with CreateProcessAsUser(), result = " << createResult;

    DWORD error = GetLastError();
    qDebug() << "Last Error = " << error;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hTokenDup);
    return TRUE;
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

#ifdef Q_OS_WIN
    CreateMyProcess(L"notepad.exe");
#endif
}
