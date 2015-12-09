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
#pragma once
//direct input
#include "USB/platform/Windows/FSDirectInputJoystick.h"
#include "USB/platform/Windows/FSDirectInputJoystickManager.h"

//Xinput
#include "USB/platform/Windows/FSXInputJoystickDeviceManager.h"
#include "USB/platform/Windows/FSXInputJoystick.h"

#include "Interfaces/IFSDeviceIDCreator.h"
#include "USB/common/FSUpdatableJoystickDeviceManager.h"
#include "common/FSTypes.h"
#include <memory>

typedef freestick::FSUpdatableJoystickDeviceManager managerType;
typedef std::unique_ptr<managerType> unique_ptr_of_managers;

namespace freestick {

    class FSWindowsJoystickDeviceManager : public IFSDeviceIDCreator
    {
    public:
        FSWindowsJoystickDeviceManager();
        virtual ~FSWindowsJoystickDeviceManager();
        void update();
        void init( );
        ElementID getNextID();
        const FSUSBJoystick * getUSBJoystickDevice(unsigned int deviceID){return static_cast<const FSUSBJoystick *>(getDevice(deviceID));}
        const FSBaseDevice * getDevice(ElementID deviceID);
        void ListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener);
        void UnListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener);

        //add or replace mapping
         //void addMappingForButton(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput);
         void addMapping(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput);
         void addMapping(unsigned int deviceID,unsigned int controlID,FSDeviceInput deviceInput);
         //FSUSBElementInfoMap lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID);
         FSUSBElementInfoMap lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID, MinMaxNumber min, MinMaxNumber max,int value);
         FSUSBElementInfoMap lookUpDeviceInputFromUSBID( unsigned int vendorUSBID, unsigned int productUSBID , unsigned int controlID,MinMaxNumber min,MinMaxNumber max,int value);
         FSUSBElementInfoMap infoMapForInputType(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor );

         bool doesDeviceHaveDeviceInput(unsigned int deviceID,FSDeviceInput inputToLookFor);
         bool doesElementHaveDeviceInputForValue(unsigned int vendorUSBID, unsigned int productUSBID ,unsigned int elementID,FSDeviceInput inputToLookFor );
         bool doesDeviceHaveDeviceInput(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor);
         bool doesDeviceHaveDeviceInputForValue(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor,int value );
         bool doesDeviceHaveDeviceInputForValue(unsigned int deviceID,FSDeviceInput inputToLookFor,  int value );

         managerType * findManagerForDevice(ElementID deviceID);

    private:
         bool _listeningForEvents;
         std::vector<unique_ptr_of_managers> managers;

    };

}
