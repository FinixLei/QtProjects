include(../TestSignalTrigger.pri)

QT += core network
QT -= gui

TARGET = TestQtService
TEMPLATE = app

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

DEFINES += _UNICODE


INCLUDEPATH += \
    $$PWD/../PluginOne \
    $$PWD/../PluginTwo

LIBS += \
    -L$$DESTDIR \
    -lPluginOne \
    -lPluginTwo \
    -L$$PWD/windows_libs \
    -lWtsApi32 \
    -lAdvApi32 \
    -lUserEnv

SOURCES += main.cpp \
    mydaemon.cpp \
    myservice.cpp \
    message_handler.cpp

include(qtservice/src/qtservice.pri)

HEADERS += \
    mydaemon.h \
    myservice.h \
    message_handler.h
