/*******************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2013-2020.

This Code is free software; you can redistribute it and/or modify it under the
terms of the zlib/libpng License as published by the Free Software Foundation;
either version 2.1 of the License, or (at your option) any later version.  This
software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the
use of this software.

Permission is granted to anyone to use this software for any purpose, including
commercial applications, and to alter it and redistribute it freely, subject to
the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim
that you wrote the original software.  If you use this software in a product,
an acknowledgment in the product documentation would be appreciated but is not
required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
*******************************************************************************/

#pragma once

#include "Interfaces/IFSDeviceIDCreator.h"
#include "USB/common/FSUpdatableJoystickDeviceManager.h"
#include "common/FSTypes.h"
#include <memory>
#include <functional>

namespace freestick
{
    using managerType            = FSUpdatableJoystickDeviceManager;
    using unique_ptr_of_managers = std::unique_ptr<managerType>;

    class FSMultJoystickDeviceManger : public IFSDeviceIDCreator
    {
    public:
        using DDHI_Callback = std::function<bool(unique_ptr_of_managers&)>;

        virtual~FSMultJoystickDeviceManger() override;
        FSMultJoystickDeviceManger();
        virtual void update();
        void init();

        elementID getNextID() const override;
        const FSUSBJoystick* getUSBJoystickDevice(const idNumber deviceID){
          return static_cast<const FSUSBJoystick*>(getDevice(deviceID));
        }
        const FSBaseDevice* getDevice(idNumber deviceID);
        void listenForAllJoysticksForEventTypes(
            const u32 eventFlags
          , IFSJoystickListener& listener);
        void unListenForAllJoysticksForEventTypes(
            const u32 eventFlags
          , IFSJoystickListener& listener);

        //add or replace mapping
        void addMapping(
            const vendorIDType vendorUSBID
          , const productIDType productUSBID
          , const idNumber controlUSBID
          , const FSDeviceInput deviceInput);
        void addMapping(
            const idNumber deviceID
          , const idNumber controlID
          , const FSDeviceInput deviceInput);
        FSUSBElementInfoMap lookUpDeviceInputFromID(
            const idNumber deviceID
          , const idNumber controlID
          , const minMaxNumber min
          , const minMaxNumber max
          , const physicalValueNumber value);
        FSUSBElementInfoMap lookUpDeviceInputFromUSBID(
            const vendorIDType vendorUSBID
          , const productIDType productUSBID
          , const idNumber controlID
          , const minMaxNumber min
          , const minMaxNumber max
          , const physicalValueNumber value);
        FSUSBElementInfoMap infoMapForInputType(
            const vendorIDType vendorUSBID
          , const productIDType productUSBID
          , const FSDeviceInput inputToLookFor);
        bool doesDeviceHaveDeviceInput(
            const idNumber deviceID
          , FSDeviceInput inputToLookFor);
        bool doesElementHaveDeviceInputForValue(
            const vendorIDType vendorUSBID
          , const productIDType productUSBID
          , const idNumber elementID
          , const FSDeviceInput inputToLookFor);
        bool doesDeviceHaveDeviceInput(
            const vendorIDType vendorUSBID
          , const productIDType productUSBID
          , const FSDeviceInput inputToLookFor);
        bool doesDeviceHaveDeviceInputForValue(
            const vendorIDType vendorUSBID
          , const productIDType productUSBID
          , const FSDeviceInput inputToLookFor
          , const physicalValueNumber value);
        bool doesDeviceHaveDeviceInputForValue(
            const idNumber deviceID
          , const FSDeviceInput inputToLookFor
          , const physicalValueNumber value);
        managerType* findManagerForDevice(
            const idNumber deviceID);

    protected:
        std::vector<unique_ptr_of_managers> managers;
        bool _listeningForEvents;

        bool DoesDeviceHaveInput(const DDHI_Callback& func);
    };
}
