#include <QCoreApplication>

#include "message_handler.h"
#include "my_windows_service.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    MyWindowsService service(argc, argv);

    qInfo() << "In the main function for MyWindowsService...";

    return service.exec();
}
