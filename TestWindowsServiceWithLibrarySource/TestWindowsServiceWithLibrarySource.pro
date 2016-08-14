include(TestWindowsServiceWithLibrarySource.pri)
include(qtservice/qtservice.pri)

QT += core
QT -= gui

CONFIG += c++11

TARGET = my_windows_service
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

DESTDIR = $$PWD/build/$$PROJ_SPEC

SOURCES += main.cpp \
    my_windows_service.cpp

HEADERS += my_windows_service.h

DISTFILES += \
    qtservice/qtservice.pri \
    TestWindowsServiceWithLibrarySource.pri
