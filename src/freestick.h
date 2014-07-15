/**************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2013.

This Code is free software; you can redistribute it and/or
modify it under the terms of the zlib/libpng License as published
by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
**************************************************************************/

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

#ifdef __APPLE__
    #include "USB/platform/NULL/FSUSBNullJoystickDeviceManager.h"
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
        // define something for simulator
        typedef freestick::FSUSBNullJoystickDeviceManager FreeStickDeviceManager;
    #elif TARGET_OS_IPHONE
        // define something for iphone
        typedef freestick::FSUSBNullJoystickDeviceManager FreeStickDeviceManager;
    #else
        #define TARGET_OS_OSX 1
        // define something for OSX
        #include "USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.h"
        typedef freestick::FSUSBMacOSXJoystickDeviceManager FreeStickDeviceManager;
    #endif
#elif __ANDROID__
    //define for android
    #include "USB/platform/Android/FSHIDAndroidJoysickDeviceManager.h"
typedef freestick::FSHIDAndroidJoysickDeviceManager FreeStickDeviceManager;

#else
    #include "USB/platform/NULL/FSUSBNullJoystickDeviceManager.h"
    typedef freestick::FSUSBNullJoystickDeviceManager FreeStickDeviceManager;
#endif

#endif // FREESTICK_H
