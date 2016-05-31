#include "worker.h"
#include <QDebug>


int Worker::myValue = 0;
QMutex Worker::leds_mutex;

Worker::Worker(QObject* parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString())
{
}

Worker::~Worker()
{
}

void Worker::run()
{
    int count = 0;
    while (count < 5) {
        ++count;
        Worker::leds_mutex.lock();

        QFile file;
        QDir::setCurrent("C:/Users/Finix/Desktop");
        file.setFileName("1.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            qCritical() << "Failed to open file";
            Worker::leds_mutex.unlock();
            break;
        }

        QTextStream out(&file);
        out     << "id: " << m_id << ", myValue = " << Worker::myValue << '\n';
        qInfo() << "id: " << m_id << ", myValue = " << Worker::myValue;
        ++Worker::myValue;

        Worker::leds_mutex.unlock();
    }

    emit finished();
}
