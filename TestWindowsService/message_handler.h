#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QFile>

class  MessageHandler
{
private:
    MessageHandler();
    ~MessageHandler();

public:
    static void setLogFile(QString file = "./mws.log");
    static void FormatMessage(QtMsgType type , const QMessageLogContext& context , const QString& msg);

private:
    static QString s_log;
};


#endif // MESSAGEHANDLER_H
