CONFIG(debug, debug|release) {
    DR_CONFIG_NAME = debug
} else {
    DR_CONFIG_NAME = release
}

DESTDIR = $$PWD/../build/$$DR_CONFIG_NAME

LIBS += -L$$DESTDIR
