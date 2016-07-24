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


void MyWindowsService::installMessageHandler()
{
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
}


void MyWindowsService::way1_GetUserNameByEnvVar()
{
    // In the system level process/service,
    // the APPDATA is
    // the UserName is "<HostName>$", e.g. "FINIX-LAPTOP$".

    qInfo() << "Way 1 - Get User Name via Environment Variable...";
    qInfo() << "APPDATA = " << qgetenv("APPDATA");
    qInfo() << "User Name = " << qgetenv("UserName");
    qInfo() << "---------------------------";
}


void MyWindowsService::way2_GetHomeLocationByQStandardPaths()
{
    // Output: "C:/Windows/system32/config/systemprofile"

    qInfo() << "Way 2 - Get User Name via QStandardPaths...";
    QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    qDebug() << homePath.first().split(QDir::separator()).last();
    qInfo() << "---------------------------";
}


void MyWindowsService::way3_GetUserNameByGetUserNameWindowsAPI()
{
    #ifdef Q_OS_WIN
    // Output: Windows User Name = "SYSTEM"

        qInfo() << "Way 3 - Get User Name via Windows API GetUserName()...";

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
    qInfo() << "---------------------------";
}


void MyWindowsService::start()
{
    // Only for "-e" option, as message handler has not been installed
    qDebug() << "Get into start().......";

    installMessageHandler();

    qInfo() << "Start MyWindowsService...";

    way1_GetUserNameByEnvVar();
    way2_GetHomeLocationByQStandardPaths();
    way3_GetUserNameByGetUserNameWindowsAPI();
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
