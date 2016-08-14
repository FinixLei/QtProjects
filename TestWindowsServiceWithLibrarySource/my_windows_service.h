#ifndef MYWINDOWSSERVICE_H
#define MYWINDOWSSERVICE_H

#include "qtservice.h"


class MyWindowsService: public QtService<QCoreApplication>
{
public:
    MyWindowsService(int argc, char* argv[]);
    ~MyWindowsService(){}

public:
    void start();
    void pause();
    void resume();
    void stop();
};

#endif // MYWINDOWSSERVICE_H
