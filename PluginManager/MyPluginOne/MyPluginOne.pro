include(../PM.pri)

QT       -= gui

TARGET = MyPluginOne
TEMPLATE = lib

DEFINES += MYPLUGINONE_LIBRARY

SOURCES += mypluginone.cpp

HEADERS += mypluginone.h\
        mypluginone_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
