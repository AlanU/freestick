/*******************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2013-2020.

This Code is free software; you can redistribute it and/or modify it under the
terms of the zlib/libpng License as published by the Free Software Foundation;
either version 2.1 of the License, or (at your option) any later version.  This
software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the
use of this software.

Permission is granted to anyone to use this software for any purpose, including
commercial applications, and to alter it and redistribute it freely, subject to
the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim
that you wrote the original software.  If you use this software in a product,
an acknowledgment in the product documentation would be appreciated but is not
required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
*******************************************************************************/

#pragma once

#include "baseClasses/FSBaseDevice.h"
#include "baseClasses/FSBaseEvent.h"
#include "baseClasses/FSBaseJoystickInfo.h" //May remove this header
#include "baseClasses/FSBaseManager.h"

#include "Interfaces/IFSJoystickListener.h"
#include "Interfaces/IFSDevice.h"
#include "Interfaces/IFSEvent.h"
#include "Interfaces/IFSJoystickInfo.h" //May remove this header

#include "USB/common/FSUSBDevice.h"
#include "USB/common/FSUSBDeviceManager.h"
#include "USB/common/FSUSBJoystickButton.h"
#include "USB/common/FSUSBJoystick.h"
#include "USB/common/FSUSBJoyStickInputElement.h"

#include "common/FSDeviceInputEvent.h"

#ifdef __APPLE__
    #include "USB/platform/NULL/FSUSBNullJoystickDeviceManager.h"
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
        // define something for simulator
        using FreeStickDeviceManager = freestick::FSUSBNullJoystickDeviceManager;
    #elif TARGET_OS_IPHONE || TARGET_OS_TV
        #include "USB/platform/iOS/FSMFIJoystickManager.h"
        // define something for iphone
        using FreeStickDeviceManager = freestick::FSMFIJoystickDeviceManager;
    #elif TARGET_OS_WATCH
        using FreeStickDeviceManager = freestick::FSUSBNullJoystickDeviceManager;
    #else
        #define TARGET_OS_OSX 1
        // define something for OSX
        #include "USB/platform/MacOSX/FSMacOSXJoystickDeviceManager.h"
        using FreeStickDeviceManager = freestick::FSMacOSXJoystickDeviceManager;
    #endif
#elif __ANDROID__
    //define for android
    #include "USB/platform/Android/jni/src/FSHIDAndroidJoysickDeviceManager.h"
    #include "USB/platform/Android/jni/src/FSJNI_Wrapper.h"
    using FreeStickDeviceManager = freestick::FSHIDAndroidJoysickDeviceManager;
#elif _WIN32
   // Windows
    #include "USB/platform/Windows/FSWindowsJoystickDeviceManager.h"
    using FreeStickDeviceManager = freestick::FSWindowsJoystickDeviceManager;
#else
    #include "USB/platform/NULL/FSUSBNullJoystickDeviceManager.h"
    using FreeStickDeviceManager = freestick::FSUSBNullJoystickDeviceManager;
#endif
