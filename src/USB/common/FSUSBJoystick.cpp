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

#include "USB/common/FSUSBJoystick.h"
using namespace freestick;
FSUSBJoystick::FSUSBJoystick()
{
}

FSUSBJoystick::~FSUSBJoystick()
{
    /** \todo delete map free memory
      */
}
FSUSBJoystick::FSUSBJoystick(unsigned int joyStickID,
                             unsigned int numberOfButtons,
                             unsigned int numberOfAnlogSticks,
                             unsigned int numberOfDigitalSticks,
                             bool  forceFeedBackSupported,
                             VenderIDType venderID,
                             ProductIDType productID):FSUSBDevice(joyStickID,
                                                         venderID,
                                                         productID)
{
    _numberOfButtons = numberOfButtons;
    _numberOfAnlogSticks = numberOfAnlogSticks;
    _numberOfDigitalSticks = numberOfDigitalSticks;
    _forceFeedBackSupported = forceFeedBackSupported;
}


void FSUSBJoystick::addInputElement(FSUSBJoyStickInputElement & element)
{
    if(_inputElementMap.find(element.getJoystickID()) == _inputElementMap.end())
        _inputElementMap[element.getJoystickID()] = element;
}
const FSUSBJoyStickInputElement * FSUSBJoystick::findInputElement(IDNumber id) const
{
    std::map<IDNumber,FSUSBJoyStickInputElement >::const_iterator itr = _inputElementMap.find(id);

    if(itr != _inputElementMap.end())
    {

        return &(itr->second);
    }
    else
       return NULL;
}

std::vector<IDNumber> FSUSBJoystick::getElementIds() const
{
    std::vector<IDNumber > elementKeys;
    std::map<IDNumber,FSUSBJoyStickInputElement >::const_iterator itr = _inputElementMap.begin();
    while(itr != _inputElementMap.end())
    {
        elementKeys.push_back(itr->first);
        ++itr;
    }
    return elementKeys;
}
