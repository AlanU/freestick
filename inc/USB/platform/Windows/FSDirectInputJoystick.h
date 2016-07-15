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
**************************************************************************/

#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "USB/common/FSUSBJoystick.h"
#include "USB/common/FSUSBJoystickDeviceManager.h"
namespace freestick {

    class FSDirectInputJoystick : public FSUSBJoystick
    {
    public:
        FSDirectInputJoystick();
        FSDirectInputJoystick(LPDIRECTINPUTDEVICE8 LPDIDJoystick,
                              ElementID joyStickID,
                              unsigned int numberOfButtons,
                              unsigned int numberOfAnlogSticks,
                              unsigned int numberOfDigitalSticks,
                              bool  forceFeedBackSupported,
                              long vendorID,
                              long productID,
                              FSUSBJoystickDeviceManager & usbJoystickManager);
        LPDIRECTINPUTDEVICE8 getDirectInputPtr(){return _LPDIDJoystick;}
        virtual ~FSDirectInputJoystick();
        virtual FSDeviceType getClassType() const {return FSDirectInputJoystickType;}
        void setCalibrated();
        bool isCalibrated() const;
    private:
        LPDIRECTINPUTDEVICE8    _LPDIDJoystick;
        FSUSBJoystickDeviceManager * _usbJoystickManager;
        static BOOL CALLBACK EnumInputObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,VOID* pContext );
        long int getCurrentValue(FSDirectInputJoystick * device,const DIDEVICEOBJECTINSTANCE* pdidoi);
        void addElement(long int usage, long int usagePage,MinMaxNumber elementId,MinMaxNumber min,MinMaxNumber max,long int value);
        bool calibrated = false;

    };
}
