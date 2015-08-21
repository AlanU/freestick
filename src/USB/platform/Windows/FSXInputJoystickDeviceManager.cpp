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
   // updateJoysticks();
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
                std::vector<DWORD>::iterator itr2 = std::find(connectedLastUpdateJoysticks.begin(),
                                                              connectedLastUpdateJoysticks.end(),
                                                               foundJoystick);
                if (itr2 != connectedLastUpdateJoysticks.end()) {
                    connectedLastUpdateJoysticks.erase(itr2);

                }else  {
                    newThisUpdate.push_back(foundJoystick);
                }
                foundThisUpdate.push_back(foundJoystick);
            }
    }
    for (int index = connectedLastUpdateJoysticks.size() - 1; index >= 0; index--) {
        DWORD deviceToDelete = connectedLastUpdateJoysticks[index];
        this->removeDevice(deviceToDelete );
    }
    std::vector<DWORD>::iterator itrAdd;
    for (itrAdd = newThisUpdate.begin(); itrAdd != newThisUpdate.end(); itrAdd++ ) {
        this->addDevice(*itrAdd);

    }

    connectedLastUpdateJoysticks = foundThisUpdate;
}

void FSXInputJoystickDeviceManager::removeDevice(DWORD device)
{
    EE_DEBUG<<"Removed Device"<<std::endl;
}

void FSXInputJoystickDeviceManager::addDevice(DWORD device)
{
    EE_DEBUG<<"Added Device"<<std::endl;

}
