#/**************************************************************************
#Created by Alan Uthoff on 10/8/2013
#Copyright (C) 2013.
#
#This Code is free software; you can redistribute it and/or
#modify it under the terms of the zlib/libpng License as published
#by the Free Software Foundation; either
#version 2.1 of the License, or (at your option) any later version.
#This software is provided 'as-is', without any express or implied warranty.
#
#In no event will the authors be held liable for any damages arising from the use of this software.
#
#Permission is granted to anyone to use this software for any purpose,
#including commercial applications, and to alter it and redistribute
#it freely, subject to the following restrictions:
#
#1. The origin of this software must not be misrepresented;
#you must not claim that you wrote the original software.
#If you use this software in a product, an acknowledgment
#in the product documentation would be appreciated but is not required.
#
#2. Altered source versions must be plainly marked as such,
#and must not be misrepresented as being the original software.
#
#3. This notice may not be removed or altered from any source distribution.
#**************************************************************************/


TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \

macx{
QMAKE_CXXFLAGS_WARN_ON= -Wall -Wno-unused-parameter -Wno-inconsistent-missing-override

LIBS += -framework IOKit \
        -framework ForceFeedback \
        -framework CoreFoundation \
        -framework GameController \
        -framework Foundation \
        -framework AppKit
         OBJECTIVE_SOURCES += ./MacOSHUD.mm
}

ios{
    LIBS += -framework GameController \
            -framework Foundation
     QMAKE_IOS_DEPLOYMENT_TARGET = 10.0
}


CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FreeStick/release/ -lFreeStick
CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FreeStick/debug/ -lFreeStick
unix:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FreeStick/release/libFreeStick.a
unix:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FreeStick/debug/libFreeStick.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FreeStick/release/FreeStick.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FreeStick/debug/FreeStick.lib

INCLUDEPATH += $$PWD/../../../inc \
               $$PWD/../../../src
DEPENDPATH += $$PWD/../FreeStick



win32:{
 LIBS += -ldinput8 -ldxguid -lcomctl32 -lOle32 -lOleAut32 -lXinput9_1_0 -lUser32
}

HEADERS += \
    MacOSHUD.h
