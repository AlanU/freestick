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

QT       += core gui quickcontrols2 qml quick
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg
VERSION = 0.0.3
TARGET = JoyStickConfig
CONFIG += c++11
android {
QT += androidextras
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-source

   message("JoyStickConfig Android Package Source")
   message($$ANDROID_PACKAGE_SOURCE_DIR)
   INCLUDEPATH +=  $$(JAVA_HOME)/include \
                   $$(JAVA_HOME)/include/darwin \
                    $$(JAVA_HOME)/include/win32 \
                    $$(JAVA_HOME)/include/linux \
                    $$NDK_ROOT/sources/android \




OTHER_FILES+= $$files(android-source/src/org/freestick/*.java) \
                  $$files(android-source/*.xml) \
CONFIG += dylib
}

TEMPLATE = app
PRECOMPILED_HEADER = $$PWD/../../../inc/freestick.h

SOURCES += main.cpp\
    baseDeviceModel.cpp \
    controllerDiagramModel.cpp \
    devicelistmodel.cpp \
        mainwindow.cpp \
        joystickconfigwidget.cpp \
    analogaxiswidget.cpp \
    controllermappingtablemodel.cpp \
    joysticklistener.cpp \
    qfreestickdevicemanger.cpp


HEADERS  += mainwindow.h \
    baseDeviceModel.h \
    controllerDiagramModel.h \
    devicelistmodel.h \
    joystickconfigwidget.h \
    analogaxiswidget.h \
    controllermappingtablemodel.h \
    joysticklistener.h \
    qfreestickdevicemanger.h

FORMS    += mainwindow.ui \
    joystickconfigwidget.ui


macx{
QMAKE_CXXFLAGS_WARN_ON= -Wall -Wno-unused-parameter -Wno-inconsistent-missing-override

LIBS += -framework IOKit \
        -framework ForceFeedback \
        -framework CoreFoundation \
        -framework GameController \
        -framework Foundation
}

ios{
    LIBS += -framework GameController \
            -framework Foundation
     QMAKE_IOS_DEPLOYMENT_TARGET = 10.0
}


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FreeStick/release/ -lFreeStick
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FreeStick/debug/ -lFreeStick
else:unix: LIBS += -L$$OUT_PWD/../FreeStick/ -lFreeStick

INCLUDEPATH += $$PWD/../../../inc \
DEPENDPATH += $$PWD/../FreeStick



win32:{
 LIBS += -ldinput8 -ldxguid -lcomctl32 -lOle32 -lOleAut32 -lXinput9_1_0 -lUser32
}

RESOURCES += \
    qml.qrc
