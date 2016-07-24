#include "windowassist.h"

#include <QObject>
#include <QDebug>

#ifdef Q_OS_WIN

#include "windows.h"
#include "Wtsapi32.h"


void GetActiveUserName()
{
    DWORD sessionId = WTSGetActiveConsoleSessionId();
    qInfo() << "session id = " << sessionId;

    wchar_t* ppBuffer[100];
    DWORD bufferSize;
    WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, sessionId, WTSUserName, ppBuffer, &bufferSize);
    qInfo() << "Windows User Name = " << QString::fromWCharArray(*ppBuffer);
}


class WindowAssistImpl
{
    WindowAssistImpl() = delete;

public:
    static LPCWSTR m_windowName;
    static HWND m_windowHandle;
    static WindowAssist* m_windowAssist;

public:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_WTSSESSION_CHANGE:
            switch (wParam)
            {
            case WTS_SESSION_LOGON:
                if (m_windowAssist != nullptr)
                {
                    qDebug() << "Capture user logon event.";
                    emit m_windowAssist->logon();

                    GetActiveUserName();
                }
                break;
            case WTS_SESSION_LOGOFF:
                if (m_windowAssist != nullptr)
                {
                    qDebug() << "Capture user logoff event.";
                    emit m_windowAssist->logoff();
                }
                break;
            case WTS_SESSION_LOCK:
                if (m_windowAssist != nullptr)
                {
                    qDebug() << "Capture user lock event.";
                    emit m_windowAssist->locked();
                }
                break;
            case WTS_SESSION_UNLOCK:
                if (m_windowAssist != nullptr)
                {
                    qDebug() << "Capture user unlock event.";
                    emit m_windowAssist->unlocked();

                    GetActiveUserName();
                }
                break;
            }
            break;
        case WM_POWERBROADCAST:
            switch (wParam)
            {
            case PBT_APMSUSPEND:
                if (m_windowAssist != nullptr)
                {
                    qDebug() << "Capture system sleep event.";
                    emit m_windowAssist->sleep();
                }
                break;
            case PBT_APMRESUMEAUTOMATIC:
                if (m_windowAssist != nullptr)
                {
                    qDebug() << "Capture system awake event.";
                    emit m_windowAssist->awake();
                }
                break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    static void createWindow()
    {
        LPCWSTR name = m_windowName;

        HINSTANCE instance = GetModuleHandle(NULL);

        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_NOCLOSE;
        wcex.lpfnWndProc = &WindowAssistImpl::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = instance;
        wcex.hIcon = NULL;
        wcex.hCursor = NULL;
        wcex.hbrBackground = NULL;
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = m_windowName;
        wcex.hIconSm = NULL;

        if (FALSE == RegisterClassEx(&wcex))
        {
            qCritical() << "RegisterClassEx failed";
            return;
        }

        m_windowHandle = CreateWindowEx(
                             WS_EX_NOACTIVATE,
                             name,
                             name,
                             NULL,
                             0, 0, 0, 0,
                             NULL,
                             NULL,
                             instance,
                             NULL);

        if (m_windowHandle == NULL)
        {
            qCritical() << "CreateWindowEx failed";
            return;
        }

        if (!WTSRegisterSessionNotification(m_windowHandle, NOTIFY_FOR_ALL_SESSIONS))
        {
            qCritical() << "Register Session Notification failed";
            return;
        }
    }

    static void destroyWindow()
    {
        HINSTANCE instance = GetModuleHandle(NULL);

        if (FALSE == CloseWindow(m_windowHandle))
        {
            qDebug() << "CloseWindow failed";
        }

        if (FALSE == DestroyWindow(m_windowHandle))
        {
            qDebug() << "DestroyWindow failed";
        }

        if (FALSE == UnregisterClass(m_windowName, instance))
        {
            qDebug() << "UnregisterClass failed";
        }

        m_windowHandle = NULL;
    }
};

/**************************************************************************************************/

LPCWSTR WindowAssistImpl::m_windowName = L"Event handler";
HWND WindowAssistImpl::m_windowHandle = NULL;
WindowAssist* WindowAssistImpl::m_windowAssist = nullptr;

/**************************************************************************************************/

WindowAssist::WindowAssist(QObject* parent)
    : QObject(parent)
{
    WindowAssistImpl::m_windowAssist = this;
    WindowAssistImpl::createWindow();
}

/**************************************************************************************************/

WindowAssist::~WindowAssist()
{
    WindowAssistImpl::destroyWindow();
    WindowAssistImpl::m_windowAssist = nullptr;
}

/**************************************************************************************************/

#endif // Q_OS_WIN
