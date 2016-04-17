#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include <QFile>
#include <QDebug>

void MessageOutput(QtMsgType type , const QMessageLogContext &context , const QString &msg);

#endif // MESSAGEHANDLER_HPP

