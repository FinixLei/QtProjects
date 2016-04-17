#include "mydaemon.h"
#include <QDebug>

MyDaemon::MyDaemon()
{
    m_one = new PluginOne;
    m_two = new PluginTwo;
    disabled = false;

    QObject::connect(m_one, &PluginOne::dataChanged, m_two, &PluginTwo::writeFile);
}

MyDaemon::~MyDaemon(){}

void MyDaemon::run() {
    qDebug() << "Starting......";
    int i = 100;
    while (i++ < 110) {
        m_one->setData(i);
    }
}

void MyDaemon::pause() {
    qDebug() << "Paused......";
    disabled = true;
}

void MyDaemon::resume() {
    qDebug() << "Resuming......";
    disabled = false;
}
