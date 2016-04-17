#ifndef MYDAEMON_H
#define MYDAEMON_H

#include "PluginOne.h"
#include "PluginTwo.h"

class MyDaemon
{
public:
    MyDaemon();
    ~MyDaemon();

    void run();
    void pause();
    void resume();

private:
    bool disabled;
    PluginOne* m_one;
    PluginTwo* m_two;
};

#endif // MYDAEMON_H
