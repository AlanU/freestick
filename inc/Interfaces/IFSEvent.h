/**************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2013.

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
#include "IFSDevice.h"
#include <assert.h>
namespace freestick 
{
    typedef enum
    {
        FS_JOYSTICK_CONNECTED_EVENT = 1<<1,
        FS_JOYSTICK_DISCONNECT_EVENT = 1<<2,
        FS_BUTTON_EVENT = 1<<3,
        FS_AXIS_EVENT = 1<<4,
        FS_TRIGGER_EVENT = 1<<5,
        FS_LAST_EVENT = 1<<6
    }FreeStickEventType;

    typedef enum
    {
        FSInputRest = 0,
        FSInputPressed = 1,
        FSInputChanged = 2

    } FSEventAction;

    class IFSEvent
    {
    public:
        virtual unsigned int getTimeStamp() = 0;
        virtual FreeStickEventType getEventType() = 0;
        virtual FSEventAction getEventAction() = 0;
        static FreeStickEventType getEventFromInputType(FSDeviceInput inputType)
        {
            if(Button0 <= inputType && inputType < LastButton  )
            {
                return FS_BUTTON_EVENT;
            }
            else if(XAxis <= inputType && inputType < LastAxis )
            {
                return FS_AXIS_EVENT;
            }
            else if(DPadUp <= inputType && inputType <= DPadRight)
            {
                return FS_BUTTON_EVENT;
            }
            else if(Trigger1 <= inputType && inputType < LastTrigger)
            {
                return FS_TRIGGER_EVENT;
            }
            //assert(false);
            return FS_LAST_EVENT;
        }
    };

}
