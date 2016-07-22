#include <QDebug>
#include <QDir>

#include "message_handler.h"
#include "my_windows_service.h"


MyWindowsService::MyWindowsService(int argc, char** argv)
    : QtService<QCoreApplication>(argc, argv, "My Windows Service")
{
    setServiceDescription("This is my Windows Service");
    setServiceFlags(QtServiceBase::CanBeSuspended);
}

void MyWindowsService::start()
{
    QString logDirName = "C:/ProgramData/MyWindowsService";
    QDir logDir(logDirName);

    if (!logDir.exists())
    {
        qDebug() << "Creating folder: " << logDirName;
        QDir().mkdir(logDirName);
    }

    QString logFile = logDirName + "/mws.log";
    MessageHandler::setLogFile(logFile);
    qInstallMessageHandler(MessageHandler::FormatMessage);

    qInfo() << "Start MyWindowsService...";
}

void MyWindowsService::stop()
{
    qInfo() << "Stop MyWindowsService...";
}

void MyWindowsService::resume()
{
    qInfo() << "Resume MyWindowsService...";
}

void MyWindowsService::pause()
{
    qInfo() << "Pause MyWindowsService...";
}
