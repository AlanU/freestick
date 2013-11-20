#-------------------------------------------------
#
# Project created by QtCreator 2013-10-07T15:05:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JoyStickConfig
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    joystickconfigwidget.cpp

HEADERS  += mainwindow.h \
    joystickconfigwidget.h

FORMS    += mainwindow.ui \
    joystickconfigwidget.ui
macx{
LIBS += -framework IOKit \
        -framework ForceFeedback \
        -framework CoreFoundation
}



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FreeStick/release/ -lFreeStick
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FreeStick/debug/ -lFreeStick
else:unix: LIBS += -L$$OUT_PWD/../FreeStick/ -lFreeStick

INCLUDEPATH += $$PWD/../FreeStick
DEPENDPATH += $$PWD/../FreeStick

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FreeStick/release/FreeStick.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FreeStick/debug/FreeStick.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../FreeStick/libFreeStick.a
