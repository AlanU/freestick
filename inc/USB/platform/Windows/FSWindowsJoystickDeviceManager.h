/**************************************************************************
   Created by Alan Uthoff on 10/8/2013
   Copyright (C) 2015.

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
*/
#pragma once
//direct input
#include "USB/platform/Windows/FSDirectInputJoystick.h"
#include "USB/platform/Windows/FSDirectInputJoystickManager.h"

//Xinput
#include "USB/platform/Windows/FSXInputJoystickDeviceManager.h"
#include "USB/platform/Windows/FSXInputJoystick.h"

#include "Interfaces/IFSDeviceIDCreator.h"
enum ManagerType
{
    DIRECT_INPUT = 0,
    XINPUT
}typedef MangerType;

namespace freestick {

    class FSWindowsJoystickDeviceManager : public FSUSBJoystickDeviceManager , public IFSDeviceIDCreator, public IFSJoystickListener
    {
    public:
        FSWindowsJoystickDeviceManager();
        virtual void update();
        virtual void init( );
        virtual DeviceID getNextID();
        virtual const FSBaseDevice * getDevice(DeviceID deviceID);
        virtual void ListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener);


        virtual void onButtonDown(FSDeviceInputEvent event);
        virtual void onButtonUp(FSDeviceInputEvent event);
        virtual void onStickMove(FSDeviceInputEvent event);
        virtual void onDisconnect(FSBaseEvent event) ;
        virtual void onConnect(FSBaseEvent event) ;

    private:
         freestick::FSDirectInputJoystickManager _directInputDeviceManager;
         freestick::FSXInputJoystickDeviceManager _xInputDeviceManger;
         bool _listeningForEvents;

    };

}
