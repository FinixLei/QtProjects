#include <QCoreApplication>
#include <QSystemSemaphore>
#include <QUuid>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QUuid uuid = QUuid::createUuid();
    QString id = uuid.toString();

    QSystemSemaphore qss("MySystemSemaphore", 1);

    int count = 0;
    while (count < 5) {
        ++count;
        qss.acquire();

        QFile file;
        QDir::setCurrent("C:/Users/Finix/Desktop");
        file.setFileName("out.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            qDebug() << "Failed to open file";
            qss.release();
            break;
        }

        QTextStream out(&file);
        out      << id << ": " << count << "\n";
        qDebug() << id << ": " << count;
        QThread::sleep(1);
        qss.release();
    }

    qDebug() << "Exit...";

    return 0;
}
