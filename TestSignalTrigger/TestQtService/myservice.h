#ifndef MYSERVICE_H
#define MYSERVICE_H

#include "qtservice.h"
#include "mydaemon.h"

class MyService : public QtService<QCoreApplication>
{
public:
    MyService(int argc, char **argv);

protected:
    void start();
    void pause();
    void resume();

private:
    MyDaemon* daemon;
};

#endif // MYSERVICE_H
