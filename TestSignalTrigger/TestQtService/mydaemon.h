#ifndef MYDAEMON_H
#define MYDAEMON_H

#include <QObject>
#include "PluginOne.h"
#include "PluginTwo.h"

class MyDaemon : public QObject
{
    Q_OBJECT
public:
    MyDaemon();
    ~MyDaemon();

    void run();
    void pause();
    void resume();

    void startProcess();

private:
    PluginOne* m_one;
    PluginTwo* m_two;
};

#endif // MYDAEMON_H
