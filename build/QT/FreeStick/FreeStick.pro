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

# turns of debug logging in release
CONFIG(release, debug|release) {
    DEFINES += "NDEBUG"
}

SOURCES += \
        ../../../src/baseClasses/FSBaseDevice.cpp \
        ../../../src/baseClasses/FSBaseManager.cpp \
        ../../../src/USB/FSUSBDevice.cpp \
        ../../../src/USB/FSUSBDeviceManager.cpp \
        ../../../src/USB/FSUSBJoystick.cpp \
        ../../../src/USB/FSUSBJoystickDeviceManager.cpp \
        ../../../src/baseClasses/FSBaseJoystickInfo.cpp \
        ../../../src/baseClasses/FSBaseEvent.cpp \
        ../../../src/FSDeviceInputEvent.cpp \
        ../../../src/USB/FSUSBJoyStickInputElement.cpp \
        ../../../src/USB/FSUSBJoystickButton.cpp \
        $$files(../../../src/USB/platform/NULL/*.cpp) \
        $$files(../../../src/3rdParty/EELog/src/*.cpp)

HEADERS += \
        $$files(../../../src/*.h) \
        ../../../src/Interfaces/IFSDevice.h \
        ../../../src/Interfaces/IFSJoystickInfo.h \
         ../../../src/Interfaces/IFSJoystickListener.h \
        ../../../src/baseClasses/FSBaseDevice.h \
        ../../../src/baseClasses/FSBaseManager.h \
        ../../../src/USB/FSUSBDevice.h \
        ../../../src/USB/FSUSBDeviceManager.h \
        ../../../src/USB/FSUSBJoystick.h \
        ../../../src/USB/FSUSBJoystickDeviceManager.h \
        ../../../src/baseClasses/FSBaseJoystickInfo.h \
        ../../../src/Interfaces/IFSEvent.h \
        ../../../src/baseClasses/FSBaseEvent.h \
        ../../../src/FSDeviceInputEvent.h \
        ../../../src/USB/FSUSBJoyStickInputElement.h \
        ../../../src/USB/FSUSBJoystickButton.h \
        ../../../src/FreeStickLog.h \
        $$files(../../../src/USB/platform/NULL/*.h) \
        $$files(../../../src/3rdParty/EELog/src/*.h)


unix:!symbian:!android {
    maemo5 {
        target.path = /opt/usr/lib
    }
    else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

android
{
  target.path = /libs/armeabi-v7a
  INSTALLS += target

}

android {
    SOURCES += $$files(../../../src/USB/platform/Android/*.cpp)

   SOURCES += $$files(../../../src/USB/platform/Android/*.c)

   HEADERS += $$files(../../../src/USB/platform/Android/*.h)

   INCLUDEPATH +=  $$(JAVA_HOME)/include \
                   $$(JAVA_HOME)/include/darwin
    message("JDK Path")
    message($$INCLUDEPATH)
  #  QT += androidextras
   # ANDROID_PACKAGE_SOURCE_DIR = $$PWD/src/USB/platform/Android/Java
    #message("Freestick Android Package Source")
   # message($$ANDROID_PACKAGE_SOURCE_DIR)

   # OTHER_FILES+= $$files(../../../src/USB/platform/Android/Java/*.java) \
          #        $$files(../../../src/USB/platform/Android/Java/*.xml)

}

macx {

SOURCES += \
         ../../../src/3rdParty/Mac/IOHID/*.c \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystick.cpp \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.cpp \


HEADERS += \
        ../../../src/3rdParty/Mac/IOHID/*.h \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystick.h \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.h \

LIBS += -framework IOKit \
        -framework ForceFeedback \
        -framework CoreFoundation \
}
