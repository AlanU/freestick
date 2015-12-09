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
const uint32_t Playstation4ControllerID = 1476;
const uint32_t LogitechVendorID = 1133;
const uint32_t LogitechDualActionID = 49686;
const uint32_t LogitechGamepadF310 = 49693;
const uint32_t OUYAVendorID = 10294;
const uint32_t OUYAControllerID = 1;
const uint32_t MicrosoftVendorID = 1118;
const uint32_t MicrosoftXbox360WindowsControllerID = 654;
const uint32_t RockCandyVenderID = 3695;
const uint32_t RockCandyXbox360ControlllerID = 3695;
const uint32_t HVG2VenderID = 2064;
const uint32_t HVG2TwinPS2 = 1 ;
const uint32_t GtronRetroSNES = 17;
const uint32_t TomeeVenderID = 7511;
const uint32_t TomeeNesUSBID = 33;
const uint32_t PCUSBSNESVenderID = 3727;
const uint32_t PCUSBSNESID = 12307;


    class FSUSBElementInfoMap
    {
         MinMaxNumber _min;
         MinMaxNumber _max;
         FSDeviceInput _inputMapping;
         FSEventAction _typeMapping; // is the value down or up on the
    public:
         inline MinMaxNumber getMax()const {return _max;}
         inline MinMaxNumber getMin()const {return _min;}
         inline FSDeviceInput getDeviceInput()const {return _inputMapping;}
         inline FSEventAction getEventMapping()const {return _typeMapping;}
        FSUSBElementInfoMap(MinMaxNumber min,MinMaxNumber max,FSDeviceInput inputMapping,FSEventAction typeMapping):_min(min),_max(max),_inputMapping(inputMapping),_typeMapping(typeMapping){}
    };

    class FSUSBDeviceManager : public FSBaseManager
    {
    private:
        // vender with map of products conatins a map of elemnets with a map of input devices with a map string key which it the min-max-inputMapping(pressed, rest ,move)
        /** \todo
         * combind vender and product ID in to on 64bit key to cut down the size of this type
         */
        std::unordered_map<DeviceID,std::unordered_map<IDNumber,FSDeviceInput> > _usageMapToInputEvent; //can only have a value of 1 or 0 where 1 is pressed and 0 is not
        std::unordered_map<DeviceID,std::unordered_map<IDNumber,std::vector<FSUSBElementInfoMap> > > _usageMapToInputRangeEvent;
    public:

       //add or replace mapping
        //TODO add addMappingForButton
        //void addMappingForButton(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput);
        void addMapping(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput);
        void addMapping(unsigned int deviceID,unsigned int controlID,FSDeviceInput deviceInput);
        //FSUSBElementInfoMap lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID);
        FSUSBElementInfoMap lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID, MinMaxNumber min, MinMaxNumber max,int value);
        FSUSBElementInfoMap lookUpDeviceInputFromUSBID( VenderIDType vendorUSBID, ProductIDType productUSBID , unsigned int controlID,MinMaxNumber min,MinMaxNumber max,int value);
        FSUSBElementInfoMap infoMapForInputType(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor );


        bool doesDeviceHaveDeviceInput(unsigned int deviceID,FSDeviceInput inputToLookFor);
        //TODO have androd overide this fuction
        bool doesElementHaveDeviceInputForValue(unsigned int vendorUSBID, unsigned int productUSBID ,unsigned int elementID,FSDeviceInput inputToLookFor );
        bool doesDeviceHaveDeviceInput(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor);
        bool doesDeviceHaveDeviceInputForValue(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor,int value );
        bool doesDeviceHaveDeviceInputForValue(unsigned int deviceID,FSDeviceInput inputToLookFor,  int value );



        FSUSBDeviceManager();
        virtual void init( );
        virtual ~FSUSBDeviceManager();
    };
}

