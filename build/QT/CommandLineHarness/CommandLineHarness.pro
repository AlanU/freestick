TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
macx{
QMAKE_CXXFLAGS_WARN_ON= -Wall -Wunused-prameter -Wno-inconsistent-missing-override

LIBS += -framework IOKit \
        -framework ForceFeedback \
        -framework CoreFoundation
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FreeStick/release/ -lFreeStick
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FreeStick/debug/ -lFreeStick
else:unix: LIBS += -L$$OUT_PWD/../FreeStick/ -lFreeStick

INCLUDEPATH += $$PWD/../../../inc \
               $$PWD/../../../src
DEPENDPATH += $$PWD/../FreeStick



win32:{
 LIBS += -ldinput8 -ldxguid -lcomctl32 -lOle32 -lOleAut32 -lXinput9_1_0 -lUser32
}
