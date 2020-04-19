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

#include "../../baseClasses/FSBaseManager.h"
#include "../../Interfaces/IFSDevice.h"
#include "common/FSTypes.h"
#include <string>
#include <unordered_map>
#include <cstdint>

namespace freestick
{
    const u32 kGravisVendorID = 1064;
    const u32 kGamePadProID = 16385;
    const u32 kDragonRiseID = 121;
    const u32 kGtron = kDragonRiseID;
    const u32 kSteelSeries3GCControllerID = 6;
    const u32 kAmazonVendorID = 6473;
    const u32 kAmazonFireGameControllerID = 1026 ;
    const u32 kGameElementsVendorID = 3888;
    const u32 kGameElementsRecoilID = 263;
    const u32 kSteelSeriesVendorID = 4152;
    const u32 kSteelSeriesFreeControllerID = 5138;
    const u32 kSonyVendorID = 1356;
    const u32 kPlaystation3ControllerID = 616;
    const u32 kPlaystation4ControllerIDV1 = 1476;
    const u32 kPlaystation4ControllerIDV2 = 2508;
    const u32 kLogitechVendorID = 1133;
    const u32 kLogitechDualActionID = 49686;
    const u32 kLogitechGamepadF710 = 49689;
    const u32 kLogitechGamepadF310 = 49693;
    const u32 kOUYAVendorID = 10294;
    const u32 kOUYAControllerID = 1;
    const u32 kMicrosoftVendorID = 1118;
    const u32 kMicrosoftXbox360WindowsControllerID = 654;
    const u32 kMicrosoftXboxOneWindowsControllerID = 746;
    const u32 kRockCandyVendorID = 3695;
    const u32 kRockCandyXbox360ControlllerID = 3695;
    const u32 kHVG2VendorID = 2064;
    const u32 kHVG2TwinPS2 = 1 ;
    const u32 kGtronRetroSNES = 17;
    const u32 kTomeeVendorID = 7511;
    const u32 kTomeeNesUSBID = 33;
    const u32 kPCUSBSNESVendorID = 3727;
    const u32 kPCUSBSNESID = 12307;
    const u32 kTomeeVendorID2 = 4797;
    const u32 kTomeeNesUSBControllerID = 53269;
    const u32 kZDVVendorID = 9571;
    const u32 kVWiredGamePadID = 1397;

    //MIFI
    const u32 kNIMBUS = 5152;
    const u32 kMIFIVenderID = 273;

    class FSUSBElementInfoMap
    {
        minMaxNumber _min;
        minMaxNumber _max;
        FSDeviceInput _inputMapping;
        FSEventAction _typeMapping; // is the value down or up on the

    public:
        minMaxNumber getMax()const{return _max;}
        minMaxNumber getMin()const{return _min;}
        FSDeviceInput getDeviceInput()const {return _inputMapping;}
        FSEventAction getEventMapping()const {return _typeMapping;}
        FSUSBElementInfoMap(
            const minMaxNumber min
          , const minMaxNumber max
          , const FSDeviceInput inputMapping
          , const FSEventAction typeMapping)
            : _min(min)
            , _max(max)
            , _inputMapping(inputMapping)
            , _typeMapping(typeMapping)
        {}
    };

    class FSUSBDeviceManager : public FSBaseManager
    {
    protected:
        /** \brief Vendor with map of products contains a map of elemnets with
          * a map of input devices with a map string key which it the
          * min-max-inputMapping(pressed, rest ,move)
          * \todo
          * combind vendor and product ID in to on 64bit key to cut down the size of this type
          */
        std::unordered_map<deviceID,std::unordered_map<idNumber,FSDeviceInput> > _usageMapToInputEvent; //can only have a value of 1 or 0 where 1 is pressed and 0 is not
        std::unordered_map<deviceID,std::unordered_map<idNumber,std::vector<FSUSBElementInfoMap> > > _usageMapToInputRangeEvent;

    public:
        //add or replace mapping
        //TODO add addMappingForButton
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
          , const physicalValueNumber value)const;
        FSUSBElementInfoMap lookUpDeviceInputFromUSBID(
            const vendorIDType vendorUSBID
          , const productIDType productUSBID
          , const idNumber controlID
          , const minMaxNumber min
          , const minMaxNumber max
          , const physicalValueNumber value)const;
        FSUSBElementInfoMap infoMapForInputType(
            const vendorIDType vendorUSBID
          , const productIDType productUSBID
          , const FSDeviceInput inputToLookFor)const;
        bool doesDeviceHaveDeviceInput(
            const idNumber deviceID
          , const FSDeviceInput inputToLookFor)const;
        /// \todo have androd overide this function
        bool doesElementHaveDeviceInputForValue(
            const vendorIDType vendorUSBID
          , const productIDType productUSBID
          , const elementID elementID
          , const FSDeviceInput inputToLookFor)const;
        bool doesDeviceHaveDeviceInput(
            const vendorIDType vendorUSBID
          , const productIDType productUSBID
          , const FSDeviceInput inputToLookFor)const;
        bool doesDeviceHaveDeviceInputForValue(
            const vendorIDType vendorUSBID
          , const productIDType productUSBID
          , const FSDeviceInput inputToLookFor
          , physicalValueNumber value)const;
        bool doesDeviceHaveDeviceInputForValue(
            const idNumber deviceID
          , const FSDeviceInput inputToLookFor
          , const physicalValueNumber value)const;

        //! Creates a 64 bit id from the vendor and product id
        static deviceID createVPId(const u32 vendor, const u32 product){
          const deviceID newID = product;
          return(( newID << 32)|vendor );
        }
        virtual ~FSUSBDeviceManager();
        FSUSBDeviceManager();
        virtual void init();
    };
}
