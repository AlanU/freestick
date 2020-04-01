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

#include "USB/common/FSUSBJoystickDeviceManager.h"
#include "USB/common/FSUpdatableJoystickDeviceManager.h"
#include <IOKit/hid/IOHIDLib.h>

namespace freestick
{
    class FSUSBMacOSXJoystickDeviceManager : public FSUpdatableJoystickDeviceManager
    {
        std::map<IOHIDDeviceRef,u32> IOHIDDeviceToIDMap;
        IOHIDManagerRef hidManagerGamePad;
        IOHIDManagerRef hidManagerJoyStick;
        void findDpad(const IOHIDDeviceRef device);

    protected:
        virtual void addDevice(const FSBaseDevice* device);
        virtual void removeDevice(const FSBaseDevice* device);
        virtual void addDevice(const IOHIDDeviceRef device);
        virtual void removeDevice(const IOHIDDeviceRef device);
        u32 getDeviceIDFromIOHIDevice(const IOHIDDeviceRef deviceRef);

    public:
        FSUSBMacOSXJoystickDeviceManager();
        virtual ~FSUSBMacOSXJoystickDeviceManager();
        virtual void init();
        static void gamepadWasAdded(
            const void* inContext
          , const IOReturn inResult
          , const void* inSender
          , const IOHIDDeviceRef device);
        static void gamepadWasRemoved(
            const void* inContext
          , const IOReturn inResult
          , const void* inSender
          , const IOHIDDeviceRef device);
        static void gamepadAction(
            const void* inContext
          , const IOReturn inResult
          , const void* inSender
          , const IOHIDValueRef value);
        static u32 createIdForElement(
            const u32 usage
          , const u32 usagePage
          , const u32 elementCookie
          , const long vendorID
          , const long productID);
        void update();
    };
}
