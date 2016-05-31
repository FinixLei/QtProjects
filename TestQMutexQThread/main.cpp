#include <QCoreApplication>
#include <QDebug>
#include <QScopedPointer>
#include "worker.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread* t1 = new QThread;
    QThread* t2 = new QThread;

    Worker* w1 = new Worker;
    Worker* w2 = new Worker;

    w1->moveToThread(t1);
    w2->moveToThread(t2);

    QObject::connect(t1, &QThread::started,  w1, &Worker::run);
    QObject::connect(w1, &Worker::finished,  t1, &QThread::quit);
    QObject::connect(w1, &Worker::finished,  [](){qInfo() << "w1 quit......";});
    QObject::connect(w1, &Worker::finished,  w1, &Worker::deleteLater);
    QObject::connect(t1, &QThread::finished, t1, &QThread::deleteLater);

    QObject::connect(t2, &QThread::started,  w2, &Worker::run);
    QObject::connect(w2, &Worker::finished,  t2, &QThread::quit);
    QObject::connect(w2, &Worker::finished,  [](){qInfo() << "w2 quit......";});
    QObject::connect(w2, &Worker::finished,  w2, &Worker::deleteLater);
    QObject::connect(t2, &QThread::finished, t2, &QThread::deleteLater);


    t1->start();
    t2->start();

    t1->wait(300);
    t2->wait(300);

    qInfo() << "At the end of main thread...";

    return 0;
}
