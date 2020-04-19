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

#include "IFSDevice.h"
#include "./common/FSTypes.h"

#include <assert.h>
#include <functional>

namespace freestick 
{
    enum FreeStickEventType
    {
        FS_JOYSTICK_CONNECTED_EVENT  = 1<<1,
        FS_JOYSTICK_DISCONNECT_EVENT = 1<<2,
        FS_BUTTON_EVENT              = 1<<3,
        FS_AXIS_EVENT                = 1<<4,
        FS_TRIGGER_EVENT             = 1<<5,
        FS_LAST_EVENT                = 1<<6,
        FS_ALL_EVENTS                = ~0
    };

    enum class FSEventAction:u32
    {
        kRest    = 0,
        kPressed = 1,
        kChanged = 2,
        kLast    = 3
    };

    struct IFSEvent
    {
        virtual FreeStickEventType getEventType() const = 0;
        virtual FSEventAction getEventAction() const = 0;
        virtual u32 getTimeStamp() const = 0;

        static FreeStickEventType getEventFromInputType(const FSDeviceInput inputType){
            if((FSDeviceInput::Button0 <= inputType) && (inputType < FSDeviceInput::LastButton)){
                return FS_BUTTON_EVENT;
            }
            if((FSDeviceInput::XAxis <= inputType) && (inputType < FSDeviceInput::LastAxis )){
                return FS_AXIS_EVENT;
            }
            if((FSDeviceInput::DPadUp <= inputType) && (inputType <= FSDeviceInput::DPadRight)){
                return FS_BUTTON_EVENT;
            }
            if((Trigger1 <= inputType) && (inputType < LastTrigger)){
                return FS_TRIGGER_EVENT;
            }
            return FS_LAST_EVENT;
        }
    };
}

namespace std
{
    template<> struct hash<freestick::FreeStickEventType>{
        std::size_t operator()(const freestick::FreeStickEventType& pt)const{
            return static_cast<freestick::u32>(pt);
        }
    };
    template<> struct hash<freestick::FSEventAction>{
        std::size_t operator()(const freestick::FSEventAction& pt)const{
            return static_cast<freestick::u32>(pt);
        }
    };
}
