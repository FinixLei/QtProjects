#ifndef PROCESSLOADER_H
#define PROCESSLOADER_H

#include <QObject>


class ProcessLoader
{
public:
    ProcessLoader();
    ~ProcessLoader();

public:

#ifdef Q_OS_WIN
    static bool loadWindowsApplication(std::wstring command);
#endif

};

#endif // PROCESSLOADER_H
