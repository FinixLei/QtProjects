#include "plugintwo.h"

#include <QDebug>


PluginTwo::PluginTwo(const QString name)
    : fileName(name), destFile(name)
{
    destFile.resize(0);
}

PluginTwo::~PluginTwo()
{
}

void PluginTwo::writeFile(int x)
{
    qDebug() << "writeFile() slot is triggered " << x;

    if (destFile.open(QFile::WriteOnly | QFile::Append)) {
        QTextStream out(&destFile);
        out << "Result: " << left << x << "\t" << x << "\n";
    }

    destFile.close();
}
