#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T15:50:26
#
#-------------------------------------------------

include(../TestSignalTrigger.pri)

QT       -= gui

TARGET = PluginTwo
TEMPLATE = lib

DEFINES += PLUGINTWO_LIBRARY

SOURCES += plugintwo.cpp

HEADERS += plugintwo.h\
        plugintwo_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
