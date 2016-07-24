#ifndef MYWINDOWSSERVICE_H
#define MYWINDOWSSERVICE_H

#include "qtservice.h"

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
};

#endif // MYWINDOWSSERVICE_H
