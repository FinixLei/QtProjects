#ifndef PLUGINONE_H
#define PLUGINONE_H

#include <QObject>
#include "pluginone_global.h"

class PLUGINONESHARED_EXPORT PluginOne : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "pluginone" FILE "PluginOne.json")

public:
    PluginOne(int d = 0);
    ~PluginOne();

    Q_INVOKABLE int getData();

public slots:
    void setData(int x);

signals:
    void dataChanged(int x);


private:
    int data;
};

Q_DECLARE_METATYPE(PluginOne*)

#endif // PLUGINONE_H
