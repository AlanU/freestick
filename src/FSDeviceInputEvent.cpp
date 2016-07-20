/**************************************************************************
Created by Alan Uthoff on 10/30/2013
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

#include "common/FSDeviceInputEvent.h"
using namespace freestick;
FSDeviceInputEvent::FSDeviceInputEvent()
{
}

FSDeviceInputEvent::FSDeviceInputEvent(FreeStickEventType eventType, FSEventAction eventAction, unsigned int timeStamp, idNumber deviceID, unsigned int controlID, float oldValue, float newValue, FSDeviceInput inputType) :
    _controlID(controlID),
    _oldValue(oldValue),
    _newValue(newValue) ,
    _inputType(inputType) ,FSBaseEvent(eventType,eventAction,timeStamp,deviceID)
{
    if(_oldValue < MIN_EVENT_VALUE )
    {
        _oldValue = MIN_EVENT_VALUE;
    }
    else if(_oldValue > MAX_EVENT_VALUE )
    {
        _oldValue = MAX_EVENT_VALUE;
    }
    if(_newValue < MIN_EVENT_VALUE)
    {
        _newValue = MIN_EVENT_VALUE;
    }
    else if(_newValue > MAX_EVENT_VALUE)
    {
        _newValue = MAX_EVENT_VALUE;
    }

}
