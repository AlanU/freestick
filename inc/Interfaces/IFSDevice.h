/**************************************************************************
Created by Alan Uthoff on 10/13/2013
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
namespace freestick {

    typedef enum
    {
        XAxis,
        YAxis,
        XAxis2,
        YAxis2,
        LastAxis,
        DPadUp,
        DPadDown,
        DPadLeft,
        DPadRight,
        LastDPad,
        Button1,//X
        ButtonX = Button1,
        Button2,//Y
        ButtonY = Button2,
        Button3,//A
        ButtonA = Button3,
        Button4,//B
        ButtonB = Button4,
        Button5,
        LeftShoulder = Button5,
        Button6,
        RightShoulder = Button6,
        Button7,
        Button8,
        Button9,//Select
        ButtonSelect = Button9,
        Button10,//Start
        ButtonStart = Button10,
        Button11,
        Button12,
        LastButton,
        Trigger1,
        Trigger2,
        LastTrigger,
        Unknown,
        LastValueUp, //use to return and event of released on the last value for the device controll (used a lot in hatswitch)
        AllInputs,
        LastInput,

    } FSDeviceInput;

    #define FS_isInputBetween(inputType,min,max)  inputType >= min && inputType < max ? true : false
    #define FS_isButtion(inputType) FS_isInputBetween(inputType,Button1,LastButton)
    #define FS_isDpad(inputType)  FS_isInputBetween(inputType,DPadUp,LastDPad)
    #define FS_isAxis(inputType)  FS_isInputBetween(inputType,XAxis,LastAxis)
    #define FS_isTrigger(inputType)  FS_isInputBetween(inputType,Trigger1,LastTrigger)

    typedef enum
    {
        FSBaseDeviceType,
        FSUSBDeviceType,
        FSUSBJoystickType,
        FSUSBMACOSXJoystickType,
        FSAndroidJoystickType,
        FSUSBNULLDeviceType

    } FSDeviceType;
    class IFSDevice
    {
    protected:
        IFSDevice(){}
        virtual ~IFSDevice(){}
    private:

    public:
        virtual unsigned int getJoystickID() const= 0;
        virtual FSDeviceType getClassType() const = 0;
    };
}
