#include "my_windows_service.h"

MyWindowsService::MyWindowsService(int argc, char* argv[])
    : QtService<QCoreApplication>(argc, argv, "My Windows Service with Source")
{
}

void MyWindowsService::start()
{
}

void MyWindowsService::stop()
{
}

void MyWindowsService::pause()
{
}

void MyWindowsService::resume()
{
}
