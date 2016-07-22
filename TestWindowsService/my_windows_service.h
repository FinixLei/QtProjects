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

};

#endif // MYWINDOWSSERVICE_H
