#-------------------------------------------------
#
# Project created by QtCreator 2013-10-07T15:10:10
#
#-------------------------------------------------

QT       -= core gui

TARGET = FreeStick
TEMPLATE = lib
CONFIG += staticlib

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
    ../../../src/USB/platform/NULL/*.cpp
HEADERS += \
        ../../../src/*.h \
        ../../../src/Interfaces/IFSDevice.h \
        ../../../src/Interfaces/IFSJoystickInfo.h \
         ../../../src/Interfaces/IFSJoystickListener.h \
        ../../../src/baseClasses/FSBaseDevice.h \
        ../../../src/baseClasses/FSBaseManager.h \
        ../../../src/USB/FSUSBDevice.h \
        ../../../src/USB/FSUSBDeviceManager.h \
        ../../../src/USB/FSUSBJoystick.h \
        ../../../src/USB/FSUSBJoystickDeviceManager.h \
        ../../../src/USB/FSUSBNullDevice.h \
        ../../../src/baseClasses/FSBaseJoystickInfo.h \
        ../../../src/Interfaces/IFSEvent.h \
        ../../../src/baseClasses/FSBaseEvent.h \
    ../../../src/FSDeviceInputEvent.h \
    ../../../src/USB/FSUSBJoyStickInputElement.h \
    ../../../src/USB/FSUSBJoystickButton.h \
    ../../../src/USB/platform/NULL/*.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

macx {

SOURCES += \
         ../../../src/3rdPary/Mac/IOHID/*.c \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystick.cpp \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.cpp \

HEADERS+= \
        ../../../src/3rdPary/Mac/IOHID/*.h \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystick.h \
        ../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.h

LIBS += -framework IOKit \
        -framework ForceFeedback \
        -framework CoreFoundation
}




