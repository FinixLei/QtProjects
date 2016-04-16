#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T15:41:09
#
#-------------------------------------------------

include(../TestSignalTrigger.pri)

QT       -= gui

TARGET = PluginOne
TEMPLATE = lib

DEFINES += PLUGINONE_LIBRARY

SOURCES += pluginone.cpp

HEADERS += pluginone.h\
        pluginone_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
