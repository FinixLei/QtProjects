#include "mypluginone.h"


MyPluginOne::MyPluginOne(int data, QString name)
    : data(data)
    , dataName(name)
{
}

MyPluginOne::~MyPluginOne()
{}

void MyPluginOne::setData(int data)
{
    this->data = data;
    emit dataChanged(data);
}

void MyPluginOne::setDataName(QString name)
{
    dataName = name;
    emit dataNameChanged(name);
}

int MyPluginOne::getData()
{
    return data;
}

QString MyPluginOne::getDataName()
{
    return dataName;
}
