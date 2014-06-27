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

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JoyStickConfig

android {
QT += androidextras
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-source
   message("JoyStickConfig Android Package Source")
   message($$ANDROID_PACKAGE_SOURCE_DIR)
OTHER_FILES+= $$files(android-source/src/org/freestick/*.java) \
                  $$files(android-source/*.xml)
#CONFIG += dylib
}

TEMPLATE = app
PRECOMPILED_HEADER = $$PWD/../../../src/FreeStick.h

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

