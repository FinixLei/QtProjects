#include <QCoreApplication>
#include <QObject>

#include "PluginOne.h"
#include "PluginTwo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PluginOne one(10);
    PluginTwo two;
    QObject::connect(&one, &PluginOne::dataChanged, &two, &PluginTwo::writeFile);

    int i = 100;
    while (i++ < 105) {
        one.setData(i);
    }

    return a.exec();
}
