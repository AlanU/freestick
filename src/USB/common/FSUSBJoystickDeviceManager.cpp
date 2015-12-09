/**************************************************************************
Created by Alan Uthoff on 10/15/2013
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

#include "USB/common/FSUSBJoystickDeviceManager.h"
#include "USB/common/FSUSBDeviceManager.h"
using namespace freestick;
FSUSBJoystickDeviceManager::FSUSBJoystickDeviceManager()
{
}

void FSUSBJoystickDeviceManager::init( )
{
    FSUSBDeviceManager::init();
}

FSUSBJoystickDeviceManager::~FSUSBJoystickDeviceManager()
{

}


uint32_t FSUSBJoystickDeviceManager::createIdForElement(uint32_t usage,uint32_t usagePage )
{
    return (usagePage << 16) | usage;
}


void FSUSBJoystickDeviceManager::updateEvents(unsigned int joystickDeviceID,FSUSBJoyStickInputElement * elementDevice, PhysicalValueNumber elementValue)
{
    static std::stack<FSUSBElementInfoMap> inputTypes;

    if (elementDevice) {
        elementDevice->getMapping(elementValue, inputTypes);
        bool isValueVaild = elementDevice->isValueInDeadZone(elementValue);

        while (!inputTypes.empty()) {
            FSUSBElementInfoMap inputType = inputTypes.top();

            FreeStickEventType eventType =  IFSEvent::getEventFromInputType(inputType.getDeviceInput());

            //pass in FSEventMaping so we can map release vs press
            if ( eventType != FS_LAST_EVENT && inputType.getDeviceInput() != LastInput) {

                if (!isValueVaild) {
                    inputOnDeviceChangedWithNormilzedValues(eventType, inputType.getEventMapping(), inputType.getDeviceInput(),
                                        joystickDeviceID, elementDevice->getJoystickID(),
                                        0, 0);
                }else  {
                    inputOnDeviceChanged(eventType, inputType.getEventMapping(), inputType.getDeviceInput(),
                                 joystickDeviceID, elementDevice->getJoystickID(),
                                 elementDevice->getValue(), 0,
                                 elementDevice->getMinValue(),
                                 elementDevice->getMaxValue());
                }
            }
            inputTypes.pop();
        }
    }
}
