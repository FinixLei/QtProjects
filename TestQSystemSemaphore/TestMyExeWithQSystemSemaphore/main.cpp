#include <QCoreApplication>
#include <QProcess>
#include <thread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::thread t1([](){QProcess::execute("./MyExe.exe");});
    std::thread t2([](){QProcess::execute("./MyExe.exe");});

    t1.join();
    t2.join();

    return 0;
}
