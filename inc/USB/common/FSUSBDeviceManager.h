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
#include <map>
#include "../../Interfaces/IFSDevice.h"
#include <string>

namespace freestick
{

const unsigned int GravisVendorID = 1064;
const unsigned int GamePadProID = 16385;
const unsigned int DragonRiseID = 121;
const unsigned int Gtron = DragonRiseID;
const unsigned int SteelSeries3GCControllerID = 6;
const unsigned int AmazonVendorID = 6473;
const unsigned int AmazonFireGameControllerID = 1026 ;
const unsigned int GameElementsVendorID = 3888;
const unsigned int GameElementsRecoilID = 263;
const unsigned int SteelSeriesVendorID = 4152;
const unsigned int SteelSeriesFreeControllerID = 5138;
const unsigned int SonyVendorID = 1356;
const unsigned int Playstation3ControllerID = 616;
const unsigned int Playstation4ControllerID = 1476;
const unsigned int LogitechVendorID = 1133;
const unsigned int LogitechDualActionID = 49686;
const unsigned int LogitechGamepadF310 = 49693;
const unsigned int OUYAVendorID = 10294;
const unsigned int OUYAControllerID = 1;
const unsigned int MicrosoftVendorID = 1118;
const unsigned int MicrosoftXbox360WindowsControllerID = 654;
const unsigned int RockCandyVenderID = 3695;
const unsigned int RockCandyXbox360ControlllerID = 3695;
const unsigned int HVG2VenderID = 2064;
const unsigned int HVG2TwinPS2 = 1 ;
const unsigned int GtronRetroSNES = 17;
const unsigned int TomeeVenderID = 7511;
const unsigned int TomeeNesUSBID = 33;
const unsigned int PCUSBSNESVenderID = 3727;
const unsigned int PCUSBSNESID = 12307;


    class FSUSBElementInfoMap
    {
         signed  long _min;
         signed long _max;
         FSDeviceInput _inputMapping;
         FSEventAction _typeMapping; // is the value down or up on the
    public:
         inline signed long getMax(){return _max;}
         inline signed long getMin(){return _min;}
         inline FSDeviceInput getDeviceInput(){return _inputMapping;}
         inline FSEventAction getEventMapping(){return _typeMapping;}
        FSUSBElementInfoMap(signed long  min,signed long max,FSDeviceInput inputMapping,FSEventAction typeMapping):_min(min),_max(max),_inputMapping(inputMapping),_typeMapping(typeMapping){}
    };

    class FSUSBDeviceManager : public FSBaseManager
    {
    private:
        // vender with map of products conatins a map of elemnets with a map of input devices with a map string key which it the min-max-inputMapping(pressed, rest ,move)
        /** \todo
         * replace std:map with boost::unordered_map for speed
         */
        std::map<unsigned int,std::map<unsigned int,std::map<IDNumber,FSDeviceInput> > > _usageMapToInputEvent; //can only have a value of 1 or 0 where 1 is pressed and 0 is not
        std::map<unsigned int,std::map<unsigned int,std::map<IDNumber,std::vector<FSUSBElementInfoMap> > > > _usageMapToInputRangeEvent;
    public:
       //add or replace mapping
        void addMappingForButton(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput);
        void addMapping(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput);
        void addMapping(unsigned int deviceID,unsigned int controlID,FSDeviceInput deviceInput);
        //FSUSBElementInfoMap lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID);
        FSUSBElementInfoMap lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID, signed long min, signed long max,int value);
        FSUSBElementInfoMap lookUpDeviceInputFromUSBID( unsigned int vendorUSBID, unsigned int productUSBID , unsigned int controlID,signed long min,signed long max,int value);


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

