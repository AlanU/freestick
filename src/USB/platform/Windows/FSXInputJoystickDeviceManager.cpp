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
    //Removed Center button since it is not avabile on Xinput Contorllers
    _usageMapToInputEvent[createVPId(MicrosoftVendorID,MicrosoftXbox360WindowsControllerID)].erase(589835);
    _usageMapToInputEvent[createVPId(MicrosoftVendorID,MicrosoftXbox360WindowsControllerID)].erase(589840);
}

void FSXInputJoystickDeviceManager::update()
{
    updateConnectJoysticks();
    updateJoysticks();
}

void  FSXInputJoystickDeviceManager::updateAnalog(unsigned int axisToLookFor , const FSXInputJoystick * xinputJoystick , unsigned int controllerID ,physicalValueNumber value )
{
    FSUSBJoyStickInputElement * element = (FSUSBJoyStickInputElement*) xinputJoystick->findInputElement(axisToLookFor) ;

    if (element) {
        if (!xinputJoystick->isCalibrated()) {
            element->setCalibrationOffsetPrecent(0.06f);
            element->recalibrate(value, element->getMinValue(), element->getMaxValue());
            return;
        }
        if (element->getValue() != value) {
            updateEvents(controllerID, element, value);
        }
        element->setValue(value);
    }
}

void  FSXInputJoystickDeviceManager::updateButton(WORD buttons,WORD xButtonToLookFor,unsigned int buttonToLookFor , const FSXInputJoystick * xinputJoystick , unsigned int controllerID )
{
    bool value = ((buttons & xButtonToLookFor)!= 0 );
    FSUSBJoyStickInputElement * pad = (FSUSBJoyStickInputElement*) xinputJoystick->findInputElement(buttonToLookFor) ;
    physicalValueNumber numValue = value ? 1 : 0;
    updateEvents(controllerID, pad, numValue);
    pad->setValue(numValue);
}

void FSXInputJoystickDeviceManager::updateJoysticks()
{
    static DWORD lastState[XUSER_MAX_COUNT]= {0,0,0,0};
	//do not as for the state of disconnected joysticks this causes performance issues
	DWORD index = 0;
    for (auto itr = _wordToIDControllerMap.begin(); itr != _wordToIDControllerMap.end();++itr)
    {
		index = itr->first;
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


               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_DPAD_UP,UP_DPAD_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_DPAD_DOWN,DOWN_DPAD_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_DPAD_LEFT,LEFT_DPAD_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_DPAD_RIGHT,RIGHT_DPAD_XINPUT_EID,xinputJoystick,joyID);

               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_A,A_BUTTON_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_B,B_BUTTON_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_X,X_BUTTON_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_Y,Y_BUTTON_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_START,START_BUTTON_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_BACK,BACK_BUTTON_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_LEFT_THUMB,LEFT_AXIS_BUTTON_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_RIGHT_THUMB,RIGHT_AXIS_BUTTON_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_LEFT_SHOULDER,LEFT_SHOULDER_BUTTON_XINPUT_EID,xinputJoystick,joyID);
               updateButton(xState.Gamepad.wButtons,XINPUT_GAMEPAD_RIGHT_SHOULDER,RIGHT_SHOULDER_BUTTON_XINPUT_EID,xinputJoystick,joyID);

               updateAnalog(XAXIS_XINPUT_EID,xinputJoystick,joyID,xState.Gamepad.sThumbLX);
               updateAnalog(YAXIS_XINPUT_EID,xinputJoystick,joyID,((int64_t)xState.Gamepad.sThumbLY*(int64_t)-1)-1);
               updateAnalog(XAXIS2_XINPUT_EID,xinputJoystick,joyID,xState.Gamepad.sThumbRX);
               updateAnalog(YAXIS2_XINPUT_EID,xinputJoystick,joyID,((int64_t)xState.Gamepad.sThumbRY*(int64_t)-1)-1);

               updateAnalog(LTRIGGER_XINPUT_EID,xinputJoystick,joyID,xState.Gamepad.bLeftTrigger);
               updateAnalog(RTRIGGER_XINPUT_EID,xinputJoystick,joyID,xState.Gamepad.bRightTrigger);


               lastState[index]= xState.dwPacketNumber;
               const_cast<FSXInputJoystick *>(xinputJoystick)->setCalibrated();
           }
        }
    }
}


void FSXInputJoystickDeviceManager::updateConnectJoysticks()
{
//TODO put this in a background thread like direct input
std::vector<DWORD> newThisUpdate;
std::vector<DWORD> foundThisUpdate;

XINPUT_STATE lastState[XUSER_MAX_COUNT];
    for (DWORD index = 0; index < XUSER_MAX_COUNT; index++)
    {
            DWORD result;
            XINPUT_STATE xState;
            ZeroMemory(&xState, sizeof(XINPUT_STATE));
            ZeroMemory(&lastState[index],sizeof(XINPUT_STATE));
            result = XInputGetState(index,&xState);
            if(result == ERROR_SUCCESS )
            {
                lastState[index] = xState;
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
    for (int index =(int) _connectedLastUpdateJoysticks.size() - 1; index >= 0; index--) {
        DWORD deviceToDelete = _connectedLastUpdateJoysticks[index];
        this->removeXInputDevice(deviceToDelete );
    }
    std::vector<DWORD>::iterator itrAdd;
    for (itrAdd = newThisUpdate.begin(); itrAdd != newThisUpdate.end(); ++itrAdd) {
        this->addXInputDevice(*itrAdd,lastState[*itrAdd]);
    }

    _connectedLastUpdateJoysticks = foundThisUpdate;
}

void FSXInputJoystickDeviceManager::removeXInputDevice(DWORD device)
{
    if(_wordToIDControllerMap.find(device) != _wordToIDControllerMap.end())
    {
        elementID id = _wordToIDControllerMap[device];
        const FSBaseDevice * joystickToDelete = getDevice(id);
        removeDevice((FSBaseDevice*)joystickToDelete);
        _wordToIDControllerMap.erase(device);
    }
    EE_DEBUG<<"Removed Device"<<std::endl;
}

void FSXInputJoystickDeviceManager::addXInputDevice(DWORD device, XINPUT_STATE & xState)
{
    if(_wordToIDControllerMap.find(device) == _wordToIDControllerMap.end())
    {
       unsigned int newId = getNextID();
       _wordToIDControllerMap[device] = newId;

      //XBox Controller
       FSXInputJoystick * newJoystick = new FSXInputJoystick(xState,device,newId,13,2,1,true,MicrosoftVendorID,MicrosoftXbox360WindowsControllerID,static_cast<FSUSBJoystickDeviceManager &>(*this));
       addDevice(newJoystick);
    }

    EE_DEBUG<<"Added XInput Device"<<std::endl;


}
