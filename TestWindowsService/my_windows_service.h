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
    void MyWindowsService::installMessageHandler();
    void MyWindowsService::way1_GetUserNameByEnvVar();
    void MyWindowsService::way2_GetHomeLocationByQStandardPaths();
    void MyWindowsService::way3_GetUserNameByGetUserNameWindowsAPI();
};

#endif // MYWINDOWSSERVICE_H
