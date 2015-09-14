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

#include "USB/platform/Windows/FSXInputJoystickDeviceManager.h"
#include "USB/platform/Windows/FSXInputJoystick.h"
#include <Windows.h>
#include <XInput.h>
#include "../../../3rdParty/EELog/src/EELog.h"
using namespace freestick;
FSXInputJoystickDeviceManager::FSXInputJoystickDeviceManager()
{

}


void FSXInputJoystickDeviceManager::update()
{
    updateConnectJoysticks();
    updateJoysticks();
}


void FSXInputJoystickDeviceManager::updateEvents(unsigned int joystickDeviceID,FSUSBJoyStickInputElement * elementDevice, long elementValue)
{
    //TODO put this in a shared location maybe a base clase
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

void FSXInputJoystickDeviceManager::updateJoysticks()
{
    static DWORD lastState[XUSER_MAX_COUNT]= {0,0,0,0};

    for (DWORD index = 0; index < XUSER_MAX_COUNT; index++)
    {
        DWORD result;
        //TODO do not do this twice
        XINPUT_STATE xState;
        ZeroMemory(&xState, sizeof(XINPUT_STATE));
        result = XInputGetState(index,&xState);
        if(result == ERROR_SUCCESS  && lastState[index] != xState.dwPacketNumber)
        {
           if(_wordToIDControllerMap.find(index) != _wordToIDControllerMap.end())
           {
               unsigned int joyID = _wordToIDControllerMap[index];
              const FSXInputJoystick * xinputJoystick = static_cast<const FSXInputJoystick*>(getDevice(joyID));

               bool Value = ((xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)!= 0 );
               FSUSBJoyStickInputElement * pad = (FSUSBJoyStickInputElement*) xinputJoystick->findInputElement(UP_DPAD_XINPUT_EID) ;
               updateEvents(joyID,pad,Value ? 1 : 0);

               Value = ((xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0) ;
               pad = (FSUSBJoyStickInputElement*) xinputJoystick->findInputElement(DOWN_DPAD_XINPUT_EID) ;
               updateEvents(joyID,pad,Value ? 1 : 0);

               Value = ((xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0) ;
               pad = (FSUSBJoyStickInputElement*) xinputJoystick->findInputElement(RIGHT_DPAD_XINPUT_EID) ;
               updateEvents(joyID,pad,Value ? 1 : 0);

               Value = ((xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0) ;
               pad = (FSUSBJoyStickInputElement*) xinputJoystick->findInputElement(LEFT_DPAD_XINPUT_EID) ;
               updateEvents(joyID,pad,Value ? 1 : 0);

               lastState[index]= xState.dwPacketNumber;
           }
        }
    }
}


void FSXInputJoystickDeviceManager::updateConnectJoysticks()
{

std::vector<DWORD> newThisUpdate;
std::vector<DWORD> foundThisUpdate;

    for (DWORD index = 0; index < XUSER_MAX_COUNT; index++)
    {
            DWORD result;
            XINPUT_STATE xState;
            ZeroMemory(&xState, sizeof(XINPUT_STATE));
            result = XInputGetState(index,&xState);
            if(result == ERROR_SUCCESS )
            {
                DWORD foundJoystick = index;
                std::vector<DWORD>::iterator itr2 = std::find(_connectedLastUpdateJoysticks.begin(),
                                                              _connectedLastUpdateJoysticks.end(),
                                                               foundJoystick);
                if (itr2 != _connectedLastUpdateJoysticks.end()) {
                    _connectedLastUpdateJoysticks.erase(itr2);

                }else  {
                    newThisUpdate.push_back(foundJoystick);
                }
                foundThisUpdate.push_back(foundJoystick);
            }
    }
    for (int index = _connectedLastUpdateJoysticks.size() - 1; index >= 0; index--) {
        DWORD deviceToDelete = _connectedLastUpdateJoysticks[index];
        this->removeXInputDevice(deviceToDelete );
    }
    std::vector<DWORD>::iterator itrAdd;
    for (itrAdd = newThisUpdate.begin(); itrAdd != newThisUpdate.end(); itrAdd++ ) {
        this->addXInputDevice(*itrAdd);

    }

    _connectedLastUpdateJoysticks = foundThisUpdate;
}

void FSXInputJoystickDeviceManager::removeXInputDevice(DWORD device)
{
    if(_wordToIDControllerMap.find(device) != _wordToIDControllerMap.end())
    {
        unsigned int id = _wordToIDControllerMap[device];
        const FSBaseDevice * joystickToDelete = getDevice(id);
        removeDevice((FSBaseDevice*)joystickToDelete);
        _wordToIDControllerMap.erase(device);
    }
    EE_DEBUG<<"Removed Device"<<std::endl;
}

void FSXInputJoystickDeviceManager::addXInputDevice(DWORD device)
{
    if(_wordToIDControllerMap.find(device) == _wordToIDControllerMap.end())
    {
       unsigned int newId = getNextID();
       _wordToIDControllerMap[device] = newId;

      //XBox Controller
       FSXInputJoystick * newJoystick = new FSXInputJoystick(device,newId,13,2,1,true,MicrosoftVendorID,MicrosoftXbox360WindowsControllerID,static_cast<FSUSBJoystickDeviceManager &>(*this));
       addDevice(newJoystick);
    }

    EE_DEBUG<<"Added XInput Device"<<std::endl;


}
