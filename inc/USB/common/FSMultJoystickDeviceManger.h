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
#include "Interfaces/IFSDeviceIDCreator.h"
#include "USB/common/FSUpdatableJoystickDeviceManager.h"
#include "common/FSTypes.h"
#include <memory>
#include <functional>

typedef freestick::FSUpdatableJoystickDeviceManager managerType;
typedef std::unique_ptr<managerType> unique_ptr_of_managers;

namespace freestick {

    class FSMultJoystickDeviceManger : public IFSDeviceIDCreator
    {
    public:
        FSMultJoystickDeviceManger();
        virtual ~FSMultJoystickDeviceManger() override;
        virtual void update();
        void init( );
        elementID getNextID() override;
        const FSUSBJoystick * getUSBJoystickDevice(idNumber deviceID){return static_cast<const FSUSBJoystick *>(getDevice(deviceID));}
        const FSBaseDevice * getDevice(idNumber deviceID);
        void ListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener);
        void UnListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener);

        //add or replace mapping
         //void addMappingForButton(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput);
         void addMapping(vendorIDType vendorUSBID,productIDType productUSBID, idNumber controlUSBID,FSDeviceInput deviceInput);
         void addMapping(idNumber deviceID, idNumber controlID,FSDeviceInput deviceInput);
         //FSUSBElementInfoMap lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID);
         FSUSBElementInfoMap lookUpDeviceInputFromID(idNumber deviceID, idNumber controlID, minMaxNumber min, minMaxNumber max,physicalValueNumber value);
         FSUSBElementInfoMap lookUpDeviceInputFromUSBID( vendorIDType vendorUSBID, productIDType productUSBID , idNumber controlID,minMaxNumber min,minMaxNumber max,physicalValueNumber value);
         FSUSBElementInfoMap infoMapForInputType(vendorIDType vendorUSBID, productIDType productUSBID ,FSDeviceInput inputToLookFor );

         bool doesDeviceHaveDeviceInput(idNumber deviceID,FSDeviceInput inputToLookFor);
         bool doesElementHaveDeviceInputForValue(vendorIDType vendorUSBID, productIDType productUSBID , idNumber elementID, FSDeviceInput inputToLookFor );
         bool doesDeviceHaveDeviceInput(vendorIDType vendorUSBID, productIDType productUSBID ,FSDeviceInput inputToLookFor);
         bool doesDeviceHaveDeviceInputForValue(vendorIDType vendorUSBID, productIDType productUSBID ,FSDeviceInput inputToLookFor,physicalValueNumber value );
         bool doesDeviceHaveDeviceInputForValue(idNumber deviceID,FSDeviceInput inputToLookFor,  physicalValueNumber value );

         managerType * findManagerForDevice(idNumber deviceID);

    protected:
         bool _listeningForEvents;
         std::vector<unique_ptr_of_managers> managers;
         bool DoesDeviceHaveInput(std::function<bool(unique_ptr_of_managers&)>const &func);
    };

}
