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

#pragma once

#include "../../baseClasses/FSBaseManager.h"
#include "../../Interfaces/IFSDevice.h"
#include "common/FSTypes.h"
#include <string>
#include <unordered_map>
#include <cstdint>

namespace freestick
{

const uint32_t GravisVendorID = 1064;
const uint32_t GamePadProID = 16385;
const uint32_t DragonRiseID = 121;
const uint32_t Gtron = DragonRiseID;
const uint32_t SteelSeries3GCControllerID = 6;
const uint32_t AmazonVendorID = 6473;
const uint32_t AmazonFireGameControllerID = 1026 ;
const uint32_t GameElementsVendorID = 3888;
const uint32_t GameElementsRecoilID = 263;
const uint32_t SteelSeriesVendorID = 4152;
const uint32_t SteelSeriesFreeControllerID = 5138;
const uint32_t SonyVendorID = 1356;
const uint32_t Playstation3ControllerID = 616;
const uint32_t Playstation4ControllerIDV1 = 1476;
const uint32_t Playstation4ControllerIDV2 = 2508;
const uint32_t Playstation5Controller = 3302;
const uint32_t LogitechVendorID = 1133;
const uint32_t LogitechDualActionID = 49686;
const uint32_t LogitechGamepadF710 = 49689;
const uint32_t LogitechGamepadF310 = 49693;
const uint32_t OUYAVendorID = 10294;
const uint32_t OUYAControllerID = 1;
const uint32_t MicrosoftVendorID = 1118;
const uint32_t MicrosoftXbox360WindowsControllerID = 654;
const uint32_t MicrosoftXboxOneWindowsControllerID = 746;
const uint32_t RockCandyVendorID = 3695;
const uint32_t RockCandyXbox360ControlllerID = 3695;
const uint32_t HVG2VendorID = 2064;
const uint32_t HVG2TwinPS2 = 1 ;
const uint32_t GtronRetroSNES = 17;
const uint32_t TomeeVendorID = 7511;
const uint32_t TomeeNesUSBID = 33;
const uint32_t PCUSBSNESVendorID = 3727;
const uint32_t PCUSBSNESID = 12307;
const uint32_t TomeeVendorID2 = 4797;
const uint32_t TomeeNesUSBControllerID = 53269;
const uint32_t ZDVVendorID = 9571;
const uint32_t VWiredGamePadID = 1397;

//MIFI
const uint32_t NIMBUS = 5152;
const uint32_t MIFIVenderID = 273;

    class FSUSBElementInfoMap
    {
         minMaxNumber _min;
         minMaxNumber _max;
         FSDeviceInput _inputMapping;
         FSEventAction _typeMapping; // is the value down or up on the
    public:
         inline minMaxNumber getMax()const {return _max;}
         inline minMaxNumber getMin()const {return _min;}
         inline FSDeviceInput getDeviceInput()const {return _inputMapping;}
         inline FSEventAction getEventMapping()const {return _typeMapping;}
        FSUSBElementInfoMap(minMaxNumber min,minMaxNumber max,FSDeviceInput inputMapping,FSEventAction typeMapping):_min(min),_max(max),_inputMapping(inputMapping),_typeMapping(typeMapping){}
    };

    class FSUSBDeviceManager : public FSBaseManager
    {
    protected:
        // vendor with map of products conatins a map of elemnets with a map of input devices with a map string key which it the min-max-inputMapping(pressed, rest ,move)
        /** \todo
         * combind vendor and product ID in to on 64bit key to cut down the size of this type
         */
        std::unordered_map<deviceID,std::unordered_map<idNumber,FSDeviceInput> > _usageMapToInputEvent; //can only have a value of 1 or 0 where 1 is pressed and 0 is not
        std::unordered_map<deviceID,std::unordered_map<idNumber,std::vector<FSUSBElementInfoMap> > > _usageMapToInputRangeEvent;
    public:

       //add or replace mapping
        //TODO add addMappingForButton
        //void addMappingForButton(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput);
        void addMapping(vendorIDType vendorUSBID, productIDType productUSBID, idNumber controlUSBID,FSDeviceInput deviceInput);
        void addMapping(idNumber deviceID, idNumber controlID, FSDeviceInput deviceInput);
        //FSUSBElementInfoMap lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID);
        virtual FSUSBElementInfoMap lookUpDeviceInputFromID(idNumber deviceID, idNumber controlID, minMaxNumber min, minMaxNumber max,physicalValueNumber value);
        virtual FSUSBElementInfoMap lookUpDeviceInputFromUSBID( vendorIDType vendorUSBID, productIDType productUSBID , idNumber controlID, minMaxNumber min, minMaxNumber max, physicalValueNumber value, bool forceAnalogLookup = false);
        FSUSBElementInfoMap infoMapForInputType(vendorIDType vendorUSBID, productIDType productUSBID ,FSDeviceInput inputToLookFor );


       bool doesDeviceHaveDeviceInput(idNumber deviceID,FSDeviceInput inputToLookFor);
        //TODO have androd overide this fuction
        virtual bool doesElementHaveDeviceInputForValue(vendorIDType vendorUSBID, productIDType productUSBID ,elementID elementID, FSDeviceInput inputToLookFor );
        virtual bool doesDeviceHaveDeviceInput(vendorIDType vendorUSBID, productIDType productUSBID ,FSDeviceInput inputToLookFor);
        virtual bool doesDeviceHaveDeviceInputForValue(vendorIDType vendorUSBID, productIDType productUSBID ,FSDeviceInput inputToLookFor,physicalValueNumber value );
        virtual bool doesDeviceHaveDeviceInputForValue(idNumber deviceID,FSDeviceInput inputToLookFor,  physicalValueNumber value );


        //creates a 64 bit id from the vendor and product id
        static deviceID createVPId(uint32_t vendor, uint32_t product ) {deviceID newID = product ; return (newID << 32) | vendor;}

        FSUSBDeviceManager();
        virtual void init( );
        virtual ~FSUSBDeviceManager();
    };
}

