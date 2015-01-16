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
        $$files(../../../src/baseClasses/*.cpp) \
        $$files(../../../src/USB/common/*.cpp) \
        $$files(../../../src/USB/platform/NULL/*.cpp) \
        $$files(../../../src/3rdParty/EELog/src/*.cpp) \
        ../../../src/FSDeviceInputEvent.cpp \


HEADERS += \
        $$files(../../../inc/*.h) \
        $$files(../../../inc/Interfaces/*.h) \
        $$files(../../../inc/baseClasses/*.h) \
        $$files(../../../inc/USB/common/*.h) \
        $$files(../../../inc/USB/*.h) \
        $$files(../../../inc/common/*.h) \
        $$files(../../../inc/USB/platform/NULL/*.h) \
        $$files(../../../src/3rdParty/EELog/src/*.h)

INCLUDEPATH += ../../../inc/USB/common \
               ../../../inc/Interfaces \
               ../../../inc/baseClasses \
               ../../../inc/USB/common \
               ../../../inc/USB \
               ../../../src/3rdParty/EELog/src \
               ../../../inc/USB/platform/NULL \
                ../../../inc/common \
                ../../../inc/USB/common \

INCLUDEPATH +=

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
#  message ( system(ndk-build  $$(NDK_ROOT)/sources/android/native_app_glue) )
message ( system(ndk-build ../../../src/USB/platform/Android))
}




android {

    SOURCES += $$files(../../../src/USB/platform/Android/jni/src/*.cpp)

  # SOURCES += $$files(../../../src/USB/platform/Android/jni/*.c)

   HEADERS += $$files(../../../inc/USB/platform/Android/jni/src/*.h)
    NDK_ROOT = $$(ANDROID_NDK_ROOT)
    !exists($$NDK_ROOT) {
           NDK_ROOT = $$DEFAULT_ANDROID_NDK_ROOT
    }
   INCLUDEPATH +=  $$(JAVA_HOME)/include \
                   $$(JAVA_HOME)/include/darwin \
                    $$(JAVA_HOME)/include/win32 \
                    $$NDK_ROOT/sources/android \
                    ../../../inc/USB/platform/Android/jni/src \
                    .


OTHER_FILES += $$files(../../../src/USB/platform/Android/jni/*.mk) \

    message("ndk path")
    message($$NDK_ROOT)
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



