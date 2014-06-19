#ifndef FREESTICK_H
#define FREESTICK_H

#include "Interfaces/IFSJoystickListener.h"
#include "Interfaces/IFSDevice.h"
#include "Interfaces/IFSEvent.h"
#include "Interfaces/IFSJoystickInfo.h" //May remove this header

#include "baseClasses/FSBaseDevice.h"
#include "baseClasses/FSBaseEvent.h"
#include "baseClasses/FSBaseJoystickInfo.h" //May remove this header
#include "baseClasses/FSBaseManager.h"

#include "USB/FSUSBDevice.h"
#include "USB/FSUSBDeviceManager.h"
#include "USB/FSUSBJoystickButton.h"
#include "USB/FSUSBJoystick.h"
#include "USB/FSUSBJoyStickInputElement.h"

#include "FSDeviceInputEvent.h"
using namespace freestick;

#ifdef __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
        // define something for simulator
        typedef FSUSBNullJoystickDeviceManager JoystickManager;
    #elif TARGET_OS_IPHONE
        // define something for iphone
        typedef FSUSBNullJoystickManager JoystickManager;
    #else
        #define TARGET_OS_OSX 1
        // define something for OSX
        #include "USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.h"
        typedef FSUSBMacOSXJoystickDeviceManager JoystickManager;
    #endif
#elif __ANDROID__
    //define for android
    #include "USB/platform/Android/FSHIDAndroidJoysickDeviceManager.h"
typedef FSHIDAndroidJoysickDeviceManager JoystickManager;

#else
    #include "USB/platform/NULL/FSUSBNullJoystickDeviceManager.h"
    typedef FSUSBNullJoystickManager JoystickManager;
#endif

#endif // FREESTICK_H
