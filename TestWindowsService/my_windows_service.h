#ifndef MYWINDOWSSERVICE_H
#define MYWINDOWSSERVICE_H

#include "qtservice.h"
#include "windowassist.h"

#ifdef Q_OS_WIN
#include <tchar.h>
#include <windows.h>
#include <Wtsapi32.h>
#include <UserEnv.h>
#endif

class MyWindowsService: public QtService<QCoreApplication>, public QObject
{
public:
    MyWindowsService(int argc, char* argv[]);

protected:
    void start();
    void pause();
    void resume();
    void stop();

private:
    void installMessageHandler();

    void way1_GetUserNameByQT();
    void way2_GetUserNameByWindowsAPI();
    void way3_GetActiveUserNameByWindowsAPIInSystemProcess();
    void way4_GetHomeLocationByQStandardPaths();
    void way5_GetHomeLocationByWindowsAPI();
    void way6_GetHomeLoactioneByWTS();
    void way7_GetEnvironmentVariables();
    void way8_GetUserRegistry();
    void testUserStuff();

    void testKeepProcess();

private:
    WindowAssist* m_windowAssist;
};

#endif // MYWINDOWSSERVICE_H
