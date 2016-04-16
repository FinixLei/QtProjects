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

class MyDaemon
{
public:
    MyDaemon()
    {
        m_one = new PluginOne;
        m_two = new PluginTwo;
        disabled = false;

        QObject::connect(m_one, &PluginOne::dataChanged, m_two, &PluginTwo::writeFile);
    }

    ~MyDaemon(){}

    void run() {
        int i = 100;
        while (i++ < 110) {
            m_one->setData(i);
            // QThread::sleep(1);
        }
    }

    void pause() {
        disabled = true;
    }

    void resume() {
        disabled = false;
    }

private:
    bool disabled;
    PluginOne* m_one;
    PluginTwo* m_two;

};


class MyService : public QtService<QCoreApplication>
{
public:
    MyService(int argc, char **argv)
    : QtService<QCoreApplication>(argc, argv, "FinixTestDaemon")
    {
        setServiceDescription("A dummy service");
        setServiceFlags(QtServiceBase::CanBeSuspended);
    }

protected:
    void start()
    {
        QCoreApplication* app = application();

        daemon = new MyDaemon();

        try {
            daemon->run();
        }
        catch(...){
            qDebug() << "MyDaemon exit!!!";
            app->quit();
        }
    }

    void pause() {
        daemon->pause();
    }

    void resume() {
        daemon->resume();
    }

private:
    MyDaemon* daemon;
};


// #include "main.moc"

int main(int argc, char **argv)
{
#if !defined(Q_OS_WIN)
    // QtService stores service settings in SystemScope, which normally require root privileges.
    // To allow testing this example as non-root, we change the directory of the SystemScope settings file.
    QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, QDir::tempPath());
    qWarning("(Example uses dummy settings file: %s/QtSoftware.conf)", QDir::tempPath().toLatin1().constData());
#endif

    MyService service(argc, argv);
    return service.exec();
}
