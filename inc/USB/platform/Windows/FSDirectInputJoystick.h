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

// TODO: Move this into translation unit.
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "USB/common/FSUSBJoystick.h"
#include "USB/common/FSUSBJoystickDeviceManager.h"

namespace freestick
{
    class FSDirectInputJoystick : public FSUSBJoystick
    {
        FSUSBJoystickDeviceManager* _usbJoystickManager;
        LPDIRECTINPUTDEVICE8 _LPDIDJoystick;
        bool calibrated = false;

        static BOOL CALLBACK EnumInputObjectsCallback(
            const DIDEVICEOBJECTINSTANCE* pdidoi
          , void* pContext );
        long int getCurrentValue(
            FSDirectInputJoystick* device
          , const DIDEVICEOBJECTINSTANCE* pdidoi);
        void addElement(
            const long int usage
          , const long int usagePage
          , const minMaxNumber elementId
          , const minMaxNumber min
          , const minMaxNumber max
          , const long int value);

    public:
        FSDirectInputJoystick();
        FSDirectInputJoystick(
            const void* lpDIDJoystick
          , const idNumber joyStickID
          , const u32 numberOfButtons
          , const u32 numberOfAnlogSticks
          , const u32 numberOfDigitalSticks
          , const bool  forceFeedBackSupported
          , const long vendorID
          , const long productID
          , const FSUSBJoystickDeviceManager& usbJoystickManager);
        LPDIRECTINPUTDEVICE8 getDirectInputPtr()const{
            return _LPDIDJoystick;
        }
        virtual ~FSDirectInputJoystick();
        virtual FSDeviceType getClassType() const {
            return FSDeviceType::kDirectInputJoystick;
        }
        void setCalibrated();
        bool isCalibrated() const;
    };
}
