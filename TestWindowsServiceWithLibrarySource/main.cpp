#include <QCoreApplication>

#include "my_windows_service.h"

int main(int argc, char *argv[])
{
    MyWindowsService service(argc, argv);

    return service.exec();
}
