#include "process_loader.h"

#ifdef Q_OS_WIN

#include <Windows.h>
#include <WinBase.h>
#include <WtsApi32.h>
#include <UserEnv.h>
#include <tchar.h>

#endif


ProcessLoader::ProcessLoader()
{}

ProcessLoader::~ProcessLoader()
{}


#ifdef Q_OS_WIN

bool ProcessLoader::loadWindowsApplication(std::wstring command)
{
    BOOL bResult = FALSE;

    DWORD dwSessionId = WTSGetActiveConsoleSessionId();
    if (dwSessionId == 0xFFFFFFFF)
    {
        return false;
    }

    HANDLE hUserToken = NULL;
    if (WTSQueryUserToken(dwSessionId, &hUserToken) == FALSE)
    {
        return false;
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

            TCHAR commandLine[MAX_PATH];
            _tcscpy_s(commandLine, MAX_PATH, command.c_str());

            // Launch the process in the client's logon session.
            bResult = CreateProcessAsUser(
                hTheToken,
                NULL,   // (LPWSTR)(path),
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

    return bResult==TRUE;
}

#endif
