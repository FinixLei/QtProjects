#include "myservice.h"
#include <QDebug>

MyService::MyService(int argc, char **argv)
    : QtService<QCoreApplication>(argc, argv, "FinixTestDaemon")
{
    setServiceDescription("A dummy service");
    setServiceFlags(QtServiceBase::CanBeSuspended);
}

void MyService::start()
{
    QCoreApplication* app = application();

    daemon = new MyDaemon();

    try {
        daemon->run();
    }
    catch(...){
        qDebug() << "MyDaemon exit!!!";
        app->quit();
    }
}

void MyService::pause() {
    daemon->pause();
}

void MyService::resume() {
    daemon->resume();
}
