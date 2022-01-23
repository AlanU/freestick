/**************************************************************************
   Created by Alan Uthoff on 10/8/2013
   Copyright (C) 2019.

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
#pragma once
#include "USB/common/FSUpdatableJoystickDeviceManager.h"
#include <unordered_map>
#include <vector>
namespace freestick
{
typedef int mfiID;
    class FSMFIJoystickDeviceManager : public FSUpdatableJoystickDeviceManager
    {
    public:
        FSMFIJoystickDeviceManager();
        virtual ~FSMFIJoystickDeviceManager();
        virtual void init( );
        const FSUSBJoystick * getUSBJoystickDevice(idNumber deviceID){return static_cast<const FSUSBJoystick *>(FSUSBDeviceManager::getDevice(deviceID));}
        virtual FSUSBElementInfoMap  lookUpDeviceInputFromUSBID( vendorIDType vendorUSBID, productIDType productUSBID , unsigned int controlID,minMaxNumber min,minMaxNumber max,int value,bool forceAnalogLookup);
        virtual bool doesDeviceHaveDeviceInput(idNumber deviceID,FSDeviceInput inputToLookFor);
    protected:
        void updateJoystickButtons(idNumber joyStickID, idNumber elementID, bool pressed,float value);
        void updateJoystickAnalog(idNumber joyStickID,idNumber elementID,float value);
        void updateConnectedControllers();
        void addMFIDevice(const void * controller);
        void removeMFIDevice(const void * device);
        virtual bool doesDeviceHaveDeviceInput(vendorIDType vendorUSBID, productIDType productUSBID ,FSDeviceInput inputToLookFor);
        virtual bool doesDeviceHaveDeviceInputForValue(vendorIDType vendorUSBID, productIDType productUSBID ,FSDeviceInput inputToLookFor,physicalValueNumber value );


       // void updateControllers();
        void connectControlesToController(const void * contorller,idNumber joyStickID);
       // uint64_t contorllerIDs = 0;
       std::vector<mfiID> _connectedLastUpdateJoysticks;
       std::unordered_map<const void *,unsigned int> _wordToIDControllerMap;
    };
}
