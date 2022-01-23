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

QT       -= core gui

TARGET = FreeStick
TEMPLATE = lib
android {
    CONFIG += shared
}else{
    CONFIG += staticlib
}
CONFIG += c++11

# turns of debug logging in release
CONFIG(release, debug|release) {
    DEFINES += "NDEBUG"
}

CONFIG(debug, debug|release) {
DESTDIR = debug
} else {
DESTDIR = release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

macx||win32{
# Clean files missed by clean
QMAKE_CLEAN += -r $$DESTDIR Makefile
QMAKE_CLEAN += -r $$DESTDIR/.qmake_stash
}

SOURCES += \
        $$files(../../../src/baseClasses/*.cpp) \
        $$files(../../../src/USB/common/*.cpp) \
        $$files(../../../src/USB/platform/NULL/*.cpp) \
        $$files(../../../src/3rdParty/EELog/src/*.cpp) \
        ../../../src/FSDeviceInputEvent.cpp \

HEADERS += \
        $$files(../../../inc/*.h) \
        $$files(../../../inc/common/*.h) \
        $$files(../../../inc/baseClasses/*.h) \
        $$files(../../../inc/Interfaces/*.h) \
        $$files(../../../inc/USB/common/*.h) \
        $$files(../../../inc/USB/*.h) \
        $$files(../../../inc/USB/platform/NULL/*.h) \
        $$files(../../../src/3rdParty/EELog/src/*.h)

INCLUDEPATH += ../../../inc \

unix:!symbian:!android {
    maemo5 {
        target.path = /opt/usr/lib
    }
    else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

android {
    target.path = /libs/armeabi-v7a
    INSTALLS += target
    #message ( system(ndk-build  $$(NDK_ROOT)/sources/android/native_app_glue) )
    #message ( system(ndk-build ../../../src/USB/platform/Android))
    SOURCES += $$files(../../../src/USB/platform/Android/jni/src/*.cpp)
    HEADERS += $$files(../../../inc/USB/platform/Android/jni/src/*.h)
    NDK_ROOT = $$(ANDROID_NDK_ROOT)
    !exists($$NDK_ROOT) {
           NDK_ROOT = $$DEFAULT_ANDROID_NDK_ROOT
    }
    INCLUDEPATH +=  $$(JAVA_HOME)/include \
                   $$(JAVA_HOME)/include/darwin \
                    $$(JAVA_HOME)/include/win32 \
                    $(JAVA_HOME)/include/linux \
                    $$NDK_ROOT/sources/android \

    ANDROID_PACKAGE_SOURCE_DIR += $$PWD/../../../src/USB/platform/Android/java


    OTHER_FILES += $$files(../../../src/USB/platform/Android/jni/*.mk) \
     $$files(../../../src/USB/platform/Android/java/src/org/freestick/*.java) \

    message("ndk path")
    message($$NDK_ROOT)
    message("JDK Path")
    message($$INCLUDEPATH)
}

macx {
    QMAKE_CXXFLAGS_WARN_ON= -Wall -Wno-unused-parameter -Wsign-compare -fobjc-arc
    SOURCES += \
         $$files(../../../src/3rdParty/Mac/IOHID/*.c) \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystick.cpp \
        ../../../src/USB/platform/MacOSX/FSMacOSXJoystickDeviceManager.cpp


    HEADERS += \
        $$files(../../../src/3rdParty/Mac/IOHID/*.h) \
        ../../../inc/USB/platform/MacOSX/FSUSBMacOSXJoystick.h \
        ../../../inc/USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.h \
        ../../../inc/USB/platform/MacOSX/FSMacOSXJoystickDeviceManager.h \
        ../../../inc/USB/platform/MacOSX/FSMacUtil.h \
        ../../../inc/USB/platform/MacOSX/GCController+hidServices.h \
        ../../../inc/intrfaces/IMuitControllerManager.h


    OBJECTIVE_SOURCES += ../../../src/USB/platform/iOS/FSMFIJoystickManager.mm \
                         ../../../src/USB/platform/iOS/FSMFIJoystick.mm \
                         ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.mm \
                         ../../../src/USB/platform/MacOSX/FSMacUtil.mm \


    LIBS += -framework IOKit \
        -framework ForceFeedback \
        -framework CoreFoundation \
        -framework GameController \
        -framework Foundation \
}

ios {
    OBJECTIVE_SOURCES += ../../../src/USB/platform/iOS/FSMFIJoystickManager.mm \
                         ../../../src/USB/platform/iOS/FSMFIJoystick.mm
    HEADERS += ../../../inc/USB/platform/iOS/FSMFIJoystickManager.h \
               ../../../inc/USB/platform/iOS/FSMFIJoystick.h
    LIBS += -framework GameController \
            -framework Foundation
    QMAKE_IOS_DEPLOYMENT_TARGET = 10.0
}

win32 {

    SOURCES += $$files(../../../src/USB/platform/Windows/*.cpp)

    HEADERS += $$files(../../../inc/USB/platform/Windows/*.h)

    LIBS += -lXinput -lUser32
}


