#-------------------------------------------------
#
# Project created by QtCreator 2013-10-07T15:10:10
#
#-------------------------------------------------

QT       -= core gui

TARGET = FreeStick
TEMPLATE = lib
android {
    CONFIG += shared
}else{
    CONFIG += staticlib
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
    $$files(../../../src/USB/platform/NULL/*.cpp)

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
    $$files(../../../src/USB/platform/NULL/*.h)

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
         ../../../src/3rdPary/Mac/IOHID/*.c \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystick.cpp \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.cpp \


HEADERS += \
        ../../../src/3rdPary/Mac/IOHID/*.h \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystick.h \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.h \

LIBS += -framework IOKit \
        -framework ForceFeedback \
        -framework CoreFoundation \
}






