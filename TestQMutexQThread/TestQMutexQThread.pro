QT += core
QT -= gui

CONFIG += c++11

TARGET = TestQSemaphore
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    worker.cpp

HEADERS += \
    worker.h
