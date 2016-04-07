#include <QCoreApplication>
#include <QFile>
#include <QObject>
#include <QPluginLoader>
#include <QDebug>

#include "MyPluginOne.h"

QObject* retrievePackage(const QString& pkgName)
{
    QString name = pkgName.toLower();

    QFile file(name);
    QPluginLoader loader(file.fileName());

    if (!loader.load())
    {
        qDebug() << "Failed to load " << name << "........";
    }

    QObject* packageObj = loader.instance();
    return packageObj;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject* pkgObj = retrievePackage("MyPluginOne");
    MyPluginOne* mpo = qobject_cast<MyPluginOne *>(pkgObj);

    QObject::connect(mpo, &MyPluginOne::dataChanged,
                     [](int data){
                        qDebug() << "Get dataChanged() Notification! It is " << data;
                     });
    QObject::connect(mpo, &MyPluginOne::dataNameChanged,
                     [](QString name){
                        qDebug() << "Get dataNameChanged() Notification! It is " << name;
                     });

    if (mpo)
    {
        mpo->setData(100);
        qInfo() << "Data = " << mpo->getData();
        mpo->setDataName("GoodBoy");
        qInfo() << "Name = " << mpo->getDataName();
    }
    else
    {
        qDebug() << "Failed to do qobject_cast";
    }

    return a.exec();
}
