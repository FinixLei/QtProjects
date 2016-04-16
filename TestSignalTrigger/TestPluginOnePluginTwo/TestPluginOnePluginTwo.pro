include(../TestSignalTrigger.pri)

QT += core
QT -= gui

CONFIG += c++11

TARGET = TestPluginOnePluginTwo
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += \
    $$PWD/../PluginOne \
    $$PWD/../PluginTwo

LIBS += \
    -L$$DESTDIR \
    -lPluginOne \
    -lPluginTwo

TEMPLATE = app

SOURCES += main.cpp
