#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QPluginLoader>
#include <QVector>

#include <iostream>

void readDependencyConfigFile(const QString& filePath, QVector<QString>& vec)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       qDebug() << "Warning: Cannot open " << filePath;
    }

    QTextStream in(&file);
    QString line;
    while(in.readLineInto(&line))
    {
        vec.push_back(line);
    }

    file.close();
}


bool goodLibPath(const QString& libPath)
{
    bool result = true;

    if (libPath.size() == 0) {
        result = false;
    }
    else if (libPath.at(0) == '#') {
        result = false;
    }
    else {
        QFile file(libPath);
        if (!file.exists())
        {
            qDebug() << "The file does not exists: " << libPath;
            result = false;
        }
    }

    return result;
}


// Load the library as a QtPlugin
QObject* loadQtPlugin(const QString& libPath)
{
    QPluginLoader loader(libPath);

    if (!loader.load())
    {
        qCritical() << "Failed to load " << libPath << ".....................";
    }

    QObject* libObj = loader.instance();
    return libObj;
}


// Load all the libraries as QtPlugin
void loadLibrariesAsQtPlugin(const QString& configFile)
{
    QVector<QString> libraryList;
    readDependencyConfigFile(configFile, libraryList);

    for(int i=0; i<libraryList.size(); ++i)
    {
        QString libPath = libraryList.at(i).simplified();  // remove spaces at the beginning and the end

        if(goodLibPath(libPath))
        {
            qDebug() << ">>>>>>>>>> " << "Loading " << libPath << "............";
            QObject* lib = loadQtPlugin(libPath);
            if (!lib)
            {
                qCritical() << "Failed to load: " << libPath;
            }
        }
        else
        {
            qCritical() << "Ignore the line: " << libPath;
        }
        qDebug() << "";
    }
}


void loadLibrariesAsNormal(const QString& configFile)
{
    QVector<QString> libraryList;
    readDependencyConfigFile(configFile, libraryList);

    for(int i=0; i<libraryList.size(); ++i)
    {
        QString libPath = libraryList.at(i).simplified();  // remove spaces at the beginning and the end

        if(goodLibPath(libPath))
        {
            qDebug() << ">>>>>>>>>> " << "Loading normal library: " << libPath << "............";
            QLibrary lib(libPath);
            if (!lib.load())
            {
                qCritical() << "Failed to load: " << libPath;
            }
        }
        else
        {
            qCritical() << "Ignore the line: " << libPath;
        }
        qDebug() << "";
    }
}

QString getEnvVar(const QString& envVar)
{
    QString value(qgetenv(envVar.toStdString().c_str()));

    if (value == "") {
        qCritical() << "No such environment variable: " << envVar;
    } else {
        qDebug() << "The value of environment variable " << envVar << " is " << value;
    }

    return value;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString configFile = "C:/Users/Finix/Desktop/dependencyList.txt";

    // loadLibrariesAsQtPlugin(configFile);
    loadLibrariesAsNormal(configFile);

    return 0;
}
