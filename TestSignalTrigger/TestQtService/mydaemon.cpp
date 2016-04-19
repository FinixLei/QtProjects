#include <QDebug>
#include <QProcess>

#include "mydaemon.h"


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

    QStringList parameters;
    parameters << "1.txt";

    // Do not use "system()" or "QProcess::execute()" or "QProcess.start()"
    // This is because they will suspend the execution of the service.
    QProcess::startDetached("notepad.exe", parameters);
}
