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
#include "USB/common/FSUSBJoystick.h"
#include <Windows.h>
#include <Xinput.h>
#include "USB/common/FSUSBJoystickDeviceManager.h"

#define UP_DPAD_XINPUT_EID    589836
#define DOWN_DPAD_XINPUT_EID  589837
#define LEFT_DPAD_XINPUT_EID  589838
#define RIGHT_DPAD_XINPUT_EID 589839

#define A_BUTTON_XINPUT_EID 589825
#define B_BUTTON_XINPUT_EID 589826
#define X_BUTTON_XINPUT_EID 589827
#define Y_BUTTON_XINPUT_EID 589828

#define BACK_BUTTON_XINPUT_EID 589834
#define START_BUTTON_XINPUT_EID 589833
#define CENTER_BUTTON_XINPUT_EID 589835

#define LEFT_SHOULDER_BUTTON_XINPUT_EID 589829
#define RIGHT_SHOULDER_BUTTON_XINPUT_EID 589830

#define LEFT_AXIS_BUTTON_XINPUT_EID 589831
#define RIGHT_AXIS_BUTTON_XINPUT_EID 589832

#define XAXIS_XINPUT_EID 65584
#define YAXIS_XINPUT_EID 65585

#define XAXIS2_XINPUT_EID 65587
#define YAXIS2_XINPUT_EID 65588

#define LTRIGGER_XINPUT_EID 65586
#define RTRIGGER_XINPUT_EID 65589

namespace  freestick {
    class FSXInputJoystick : public FSUSBJoystick
    {
    public:
        FSXInputJoystick(XINPUT_STATE & state,
                         DWORD id, idNumber joyStickID,
                         unsigned int numberOfButtons,
                         unsigned int numberOfAnlogSticks,
                         unsigned int numberOfDigitalSticks,
                         bool  forceFeedBackSupported,
                         long vendorID,
                         long productID,
                         FSUSBJoystickDeviceManager & usbJoystickManager);
        void addXinputElements(XINPUT_STATE & state);
        void addButtonElement(unsigned int buttonID);
        void addElement(unsigned int buttonID,minMaxNumber min,minMaxNumber max,physicalValueNumber currentValue);
        void setCalibrated();
        bool isCalibrated() const;
        virtual FSDeviceType getClassType() const {return FSXInputJoystickType;}
        void vibrate() const override;
        void stopVibrate() const override;
    private:
        DWORD _id;
        FSUSBJoystickDeviceManager * _usbJoystickManager = nullptr;
        unsigned int _totalButtonNumber = 0;
        bool calibrated = false;


    };
}
