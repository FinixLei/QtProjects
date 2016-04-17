include(../TestSignalTrigger.pri)

QT += core network
QT -= gui

CONFIG += c++11

TARGET = TestQtService
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += \
    $$PWD/../PluginOne \
    $$PWD/../PluginTwo

LIBS += \
    -L$$DESTDIR \
    -lPluginOne \
    -lPluginTwo

SOURCES += main.cpp \
    mydaemon.cpp \
    myservice.cpp \
    message_handler.cpp

include(qtservice/src/qtservice.pri)

HEADERS += \
    mydaemon.h \
    myservice.h \
    message_handler.h
