#include <QObject>
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

#include <QTextStream>
#include <QDateTime>
#include <QStringList>
#include <QDir>
#include <QSettings>
#include <QThread>

#include "PluginOne.h"
#include "PluginTwo.h"

#include "qtservice.h"
#include "myservice.h"
#include "message_handler.h"


int main(int argc, char **argv)
{
#ifdef Q_OS_WIN
    MessageHandler::setLogFile("C:/MyService.log");
#endif
    qInstallMessageHandler(MessageHandler::FormatMessage);

#if !defined(Q_OS_WIN)
    // QtService stores service settings in SystemScope, which normally require root privileges.
    // To allow testing this example as non-root, we change the directory of the SystemScope settings file.
    QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, QDir::tempPath());
    qWarning("(Example uses dummy settings file: %s/QtSoftware.conf)", QDir::tempPath().toLatin1().constData());
#endif

    MyService service(argc, argv);
    return service.exec();
}
