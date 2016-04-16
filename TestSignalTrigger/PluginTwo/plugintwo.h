#ifndef PLUGINTWO_H
#define PLUGINTWO_H

#include <QObject>
#include <QFile>
#include <QTextStream>

#include "plugintwo_global.h"

class PLUGINTWOSHARED_EXPORT PluginTwo : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugintwo" FILE "PluginTwo.json")

public:
    PluginTwo(const QString name = "PluginTwoFile.txt");
    ~PluginTwo();

public slots:
    void writeFile(int x);

private:
    QFile destFile;
    QString fileName;
};

#endif // PLUGINTWO_H
