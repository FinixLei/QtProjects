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

SOURCES += main.cpp

include(qtservice/src/qtservice.pri)
