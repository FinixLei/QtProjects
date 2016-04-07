#ifndef MYPLUGINONE_H
#define MYPLUGINONE_H

#include "mypluginone_global.h"

#include <QObject>

class MYPLUGINONESHARED_EXPORT MyPluginOne : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "mypluginone" FILE "MyPluginOne.json")

public:
    MyPluginOne(int data=-1, QString name="InitialName");
    ~MyPluginOne();

public slots:
    void setData(int data);
    void setDataName(QString name);

public:
    int getData();
    QString getDataName();

signals:
    void dataChanged(int data);
    void dataNameChanged(QString name);

private:
    int data;
    QString dataName;
};

Q_DECLARE_METATYPE(MyPluginOne*)

#endif // MYPLUGINONE_H
