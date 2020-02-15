/**************************************************************************
Created by Alan Uthoff on 10/15/2013
Copyright (C) 2013

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

#pragma once
#include "USB/common/FSUSBJoystickDeviceManager.h"
#include "USB/common/FSUpdatableJoystickDeviceManager.h"
#include <IOKit/hid/IOHIDLib.h>
namespace freestick
{
    class FSUSBMacOSXJoystickDeviceManager : public FSUpdatableJoystickDeviceManager
    {
    public:
        FSUSBMacOSXJoystickDeviceManager();
        virtual ~FSUSBMacOSXJoystickDeviceManager();
        virtual void init( );
        static void gamepadWasAdded(void* inContext, IOReturn inResult, void* inSender, IOHIDDeviceRef device);
        static void gamepadWasRemoved(void* inContext, IOReturn inResult, void* inSender, IOHIDDeviceRef device);
        static void gamepadAction(void* inContext, IOReturn inResult, void* inSender, IOHIDValueRef value);
        static uint32_t createIdForElement(uint32_t usage, uint32_t usagePage, uint32_t elementCookie, long vendorID, long productID );

        void update();
    private:
        IOHIDManagerRef  hidManagerGamePad;
        IOHIDManagerRef  hidManagerJoyStick;
        std::map<IOHIDDeviceRef,unsigned int> IOHIDDeviceToIDMap;
        void findDpad(IOHIDDeviceRef device);
    protected:
        virtual void addDevice(FSBaseDevice * device);
        virtual void removeDevice(FSBaseDevice * device);
        virtual void addDevice(IOHIDDeviceRef  device);
        virtual void removeDevice(IOHIDDeviceRef device);
        unsigned int getDeviceIDFromIOHIDevice(IOHIDDeviceRef deviceRef);

    };
}

