#include <QDebug>
#include <QMessageLogger>
#include <QDateTime>
#include <QTextStream>
#include <QFile>

#include "message_handler.h"


QString MessageHandler::s_log = "C:/MyService.log";

void MessageHandler::setLogFile(QString file)
{
    s_log = file;
}

void MessageHandler::FormatMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QFile logFile(MessageHandler::s_log);
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);

    QString log("");
    log += QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") + QString(" ");

    switch(type)
    {
    case QtDebugMsg:
        log += QString("[Debug]");
        break;

    case QtInfoMsg:
        log += QString("[Info]");
        break;

    case QtWarningMsg:
        log += QString("[Warn]");
        break;

    case QtCriticalMsg:
        log += QString("[Critical]");
        break;

    case QtFatalMsg:
        log += QString("[Fatal]");
        abort();
        break;

    default:
        log += QString("[UnknownLogType]");
        break;
    };

    log += QString(context.file)
           + QString(", Line ")
           + QString::number(context.line)
           + QString(": %1\n").arg(msg);

    QTextStream text_stream(&logFile);
    text_stream << log;
    logFile.flush();
    logFile.close();

    mutex.unlock();
}
