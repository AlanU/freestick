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

#include "common/FSTypes.h"

namespace freestick
{
    enum FSDeviceInput
    {
        XAxis,//Left
        YAxis,//Left
        XAxis2,//Right
        YAxis2,//Right
        XAxis3,
        YAxis3,
        LastAxis,
        DPadUp,
        DPadDown,
        DPadLeft,
        DPadRight,
        LastDPad,
        //use the HTML standard https://dvcs.w3.org/hg/gamepad/raw-file/default/gamepad.html excpet for button  12-15
        Button0,//A
        ButtonA = Button0,
        Button1,//B
        ButtonB = Button1,
        Button2,//X
        ButtonX = Button2,
        Button3,//Y
        ButtonY = Button3,
        Button4,
        LeftShoulder = Button4,
        Button5,
        RightShoulder = Button5,
        Button6,//Left digital shoulder button L2
        LeftShoulder2 = Button6,
        Button7,//Right digital sholder button R
        RightShoulder2 = Button7,
        Button8,//Select/back
        ButtonSelect = Button8,
        Button9,//Start
        ButtonStart = Button9,
        Button10,//L3
        Axis1Button = Button10,
        Button11,//R3
        Axis2Button = Button11,
        Button12,
        Button13,
        Button14,
        Button15,
        Button16,
        ButtonCenter,//example xbox button
        Button18,
        Button19,
        Button20,
        Button21,
        Button22,
        Button23,
        Button24,
        ButtonHome,
        LastButton,
        Trigger1,//Left
        Trigger2,//Right
        LastTrigger,
        Unknown,
        LastValueUp, //use to return and event of released on the last value for the device controll (used a lot in hatswitch)
        AllInputs,
        LastInput,
    };

    #define FS_isInputBetween(inputType, min, max)  ((inputType >= min) && ((inputType < max) ? true : false))
    #define FS_isButtion(inputType)                 FS_isInputBetween(inputType, Button0, LastButton)
    #define FS_isDpad(inputType)                    FS_isInputBetween(inputType, DPadUp, LastDPad)
    #define FS_isAxis(inputType)                    FS_isInputBetween(inputType, XAxis, LastAxis)
    #define FS_isTrigger(inputType)                 FS_isInputBetween(inputType, Trigger1, LastTrigger)

    enum class FSDeviceType:u32
    {
        kBase,
        kUSB,
        kUSBJoystick,
        kUSBMACOSXJoystick,
        kAndroidJoystick,
        kDirectInputJoystick,
        kUSBNULL
    };

    class IFSDevice
    {
    protected:
        virtual ~IFSDevice() = default;
        IFSDevice() = default;

    public:
        virtual FSDeviceType getClassType() const = 0;
        virtual idNumber getJoystickID() const = 0;
    };
}
