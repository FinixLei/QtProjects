#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QMutex>
#include <QUuid>
#include <QFile>
#include <QDir>


class Worker : public QObject
{
    Q_OBJECT

private:
    static int myValue;
    static QMutex leds_mutex;
    QString m_id;

public:
    Worker(QObject* parent = nullptr);
    ~Worker();

public slots:
    void run();

signals:
    void finished();
    void error(QString err);
};

#endif // MYTHREAD_H
