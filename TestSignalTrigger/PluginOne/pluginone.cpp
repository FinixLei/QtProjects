#include "pluginone.h"


PluginOne::PluginOne(int d) : data(d)
{
}

PluginOne::~PluginOne()
{
}

int PluginOne::getData() {
    return data;
}

void PluginOne::setData(int x) {
    data = x;
    emit dataChanged(x);
}
