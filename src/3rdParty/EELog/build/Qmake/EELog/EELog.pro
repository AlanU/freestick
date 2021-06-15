#-------------------------------------------------
#
# Project created by QtCreator 2014-06-19T23:31:34
#
#-------------------------------------------------

QT       -= core gui

TARGET = EELog
TEMPLATE = lib
CONFIG += staticlib

# turns of debug logging in release
CONFIG(release, debug|release) {
    DEFINES += "NDEBUG"
}


SOURCES += $$files($$PWD/../../../src/*.cpp)

HEADERS += $$files($$PWD/../../../src/*.h)

INCLUDEPATH += $$PWD/../../../src/
unix {
    target.path = /usr/lib
    INSTALLS += target
}
