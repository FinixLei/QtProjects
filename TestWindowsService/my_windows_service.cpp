#include <QDebug>
#include <QDir>
#include <QStandardPaths>

#include "message_handler.h"
#include "my_windows_service.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include <QProcess>


MyWindowsService::MyWindowsService(int argc, char** argv)
    : QtService<QCoreApplication>(argc, argv, "My Windows Service")
{
    setServiceDescription("This is my Windows Service");
    setServiceFlags(QtServiceBase::CanBeSuspended);
}

void MyWindowsService::start()
{
    qDebug() << "Get into start().......";

    // Install Message Handler

    QString logDirName = "C:/ProgramData/MyWindowsService";
    QDir logDir(logDirName);

    if (!logDir.exists())
    {
        qDebug() << "Creating folder: " << logDirName;
        QDir().mkdir(logDirName);
    }

    QString logFile = logDirName + "/mws.log";

    // Remove the Macro defined in winbase.h
    #ifdef FormatMessage
    #undef FormatMessage
        message_handler::MessageHandler::setLogFile(logFile);
        qInstallMessageHandler(message_handler::MessageHandler::FormatMessage);
    #endif

    qInfo() << "Start MyWindowsService...";
    qInfo() << "APPDATA = " << qgetenv("APPDATA");
    qInfo() << "User Name = " << qgetenv("UserName");

    QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    qDebug() << homePath.first().split(QDir::separator()).last();

    #ifdef Q_OS_WIN
        wchar_t acUserName[200];
        DWORD nUserName = sizeof(acUserName);
        if (GetUserName(acUserName, &nUserName))
        {
            // Translate wchar_t * to QString
            qInfo() << "Windows User Name = " << QString::fromWCharArray(acUserName);
        }
    #elif Q_OS_UNIX
        QCoreApplication coreApplication(argc, argv);
        QProcess process;
        QObject::connect(&process, &QProcess::finished, [&coreApplication, &process](int exitCode, QProcess::ExitStatus exitStatus) {
            qDebug() << process.readAllStandardOutput();
            coreApplication.quit();
        });
        process.start("whoami");
    #endif
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
