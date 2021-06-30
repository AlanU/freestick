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

#include "USB/common/FSUSBDeviceManager.h"
#include "baseClasses/FSBaseManager.h"
#include "USB/common/FSUSBDevice.h"
#include "Interfaces/IFSDevice.h"
#include <algorithm>
#include <cstdint>
#include <array>
using namespace freestick;
//const uint32_t VMSVenderUSBID = 1212;
//const uint32_t VMSProductUSBID = 49153;

FSUSBDeviceManager::FSUSBDeviceManager()
{
    /** \todo
    * populate map _usageMapToInputEvent
    */
    //_usageMapToInputRangeEvent[createVPId(VMSVenderUSBID,VMSProductUSBID)][589872].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    //_usageMapToInputRangeEvent[createVPId(VMSVenderUSBID,VMSProductUSBID)][589873].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));


    /*_usageMapToInputEvent[createVPId(VMSVenderUSBID,VMSProductUSBID)][589835] = ButtonB;
    _usageMapToInputEvent[createVPId(VMSVenderUSBID,VMSProductUSBID)][589836] = ButtonA;
    _usageMapToInputEvent[createVPId(VMSVenderUSBID,VMSProductUSBID)][589837] = ButtonY;
    _usageMapToInputEvent[createVPId(VMSVenderUSBID,VMSProductUSBID)][589838] = ButtonX;
    _usageMapToInputEvent[createVPId(VMSVenderUSBID,VMSProductUSBID)][589839] = ButtonSelect;
    */

    _usageMapToInputEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][589826] = ButtonB;
    _usageMapToInputEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][589827] = ButtonA;
    _usageMapToInputEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][589825] = ButtonY;
    _usageMapToInputEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][589828] = ButtonX;


    _usageMapToInputEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][589832] = RightShoulder;
    _usageMapToInputEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][589831] = LeftShoulder;


    _usageMapToInputEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][589833] = ButtonSelect;
    _usageMapToInputEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][589834] = ButtonStart;


    _usageMapToInputRangeEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][65585].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][65585].push_back(FSUSBElementInfoMap(255,255,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][65585].push_back(FSUSBElementInfoMap(128,128,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][65584].push_back(FSUSBElementInfoMap(0,0,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][65584].push_back(FSUSBElementInfoMap(255,255,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(PCUSBSNESVendorID,PCUSBSNESID)][65584].push_back(FSUSBElementInfoMap(128,128,LastValueUp,FSInputRest));


    _usageMapToInputEvent[createVPId(TomeeVendorID2,TomeeNesUSBControllerID)][589825] = ButtonB;
    _usageMapToInputEvent[createVPId(TomeeVendorID2,TomeeNesUSBControllerID)][589826] = ButtonA;

    _usageMapToInputEvent[createVPId(TomeeVendorID2,TomeeNesUSBControllerID)][589834] = ButtonStart;
    _usageMapToInputEvent[createVPId(TomeeVendorID2,TomeeNesUSBControllerID)][589833] = ButtonSelect;


    _usageMapToInputRangeEvent[createVPId(TomeeVendorID2,TomeeNesUSBControllerID)][65585].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(TomeeVendorID2,TomeeNesUSBControllerID)][65585].push_back(FSUSBElementInfoMap(255,255,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(TomeeVendorID2,TomeeNesUSBControllerID)][65585].push_back(FSUSBElementInfoMap(127,127,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[createVPId(TomeeVendorID2,TomeeNesUSBControllerID)][65584].push_back(FSUSBElementInfoMap(0,0,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(TomeeVendorID2,TomeeNesUSBControllerID)][65584].push_back(FSUSBElementInfoMap(255,255,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(TomeeVendorID2,TomeeNesUSBControllerID)][65584].push_back(FSUSBElementInfoMap(127,127,LastValueUp,FSInputRest));



    _usageMapToInputEvent[createVPId(TomeeVendorID,TomeeNesUSBID)][589825] = ButtonB;
    _usageMapToInputEvent[createVPId(TomeeVendorID,TomeeNesUSBID)][589826] = ButtonA;

    _usageMapToInputEvent[createVPId(TomeeVendorID,TomeeNesUSBID)][589827] = ButtonSelect;
    _usageMapToInputEvent[createVPId(TomeeVendorID,TomeeNesUSBID)][589828] = ButtonStart;


    _usageMapToInputRangeEvent[createVPId(TomeeVendorID,TomeeNesUSBID)][65585].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(TomeeVendorID,TomeeNesUSBID)][65585].push_back(FSUSBElementInfoMap(255,255,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(TomeeVendorID,TomeeNesUSBID)][65585].push_back(FSUSBElementInfoMap(127,127,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[createVPId(TomeeVendorID,TomeeNesUSBID)][65584].push_back(FSUSBElementInfoMap(0,0,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(TomeeVendorID,TomeeNesUSBID)][65584].push_back(FSUSBElementInfoMap(255,255,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(TomeeVendorID,TomeeNesUSBID)][65584].push_back(FSUSBElementInfoMap(127,127,LastValueUp,FSInputRest));

    // SteelSeries ("Gtron") Gtron Retro Classic FC SNES Controller
    //has the same vendor id as DragonRise
    //TODO add in start and select
    _usageMapToInputEvent[createVPId(Gtron,GtronRetroSNES)][589826] = ButtonB ;
    _usageMapToInputEvent[createVPId(Gtron,GtronRetroSNES)][589827] = ButtonA ;
    _usageMapToInputEvent[createVPId(Gtron,GtronRetroSNES)][589825] = ButtonY;
    _usageMapToInputEvent[createVPId(Gtron,GtronRetroSNES)][589828] = ButtonX;

    _usageMapToInputEvent[createVPId(Gtron,GtronRetroSNES)][589830] = RightShoulder;
    _usageMapToInputEvent[createVPId(Gtron,GtronRetroSNES)][589829] = LeftShoulder;


    _usageMapToInputEvent[createVPId(Gtron,GtronRetroSNES)][589833] = ButtonSelect;
    _usageMapToInputEvent[createVPId(Gtron,GtronRetroSNES)][589834] = ButtonStart;


    _usageMapToInputRangeEvent[createVPId(Gtron,GtronRetroSNES)][65585].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(Gtron,GtronRetroSNES)][65585].push_back(FSUSBElementInfoMap(255,255,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(Gtron,GtronRetroSNES)][65585].push_back(FSUSBElementInfoMap(127,127,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[createVPId(Gtron,GtronRetroSNES)][65584].push_back(FSUSBElementInfoMap(0,0,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(Gtron,GtronRetroSNES)][65584].push_back(FSUSBElementInfoMap(255,255,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(Gtron,GtronRetroSNES)][65584].push_back(FSUSBElementInfoMap(127,127,LastValueUp,FSInputRest));


    //First ps2 port
    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589827] =  ButtonA;
    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589826] =  ButtonB;
    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589828] =  ButtonY;
    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589825] =  ButtonX;

    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589831] =  LeftShoulder;
    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589832] =  RightShoulder;
    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589829] =  LeftShoulder2;
    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589830] =  RightShoulder2;

    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589835] = Axis1Button;
    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589836] = Axis2Button;

    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589833] =  ButtonSelect;
    _usageMapToInputEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][589834] =  ButtonStart;

    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65593].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65593].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65593].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65589].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(HVG2VendorID,HVG2TwinPS2)][65586].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));


    // SteelSeries ("DragonRise") 3GC controller
    // Has a very "noisy" analog axis ID 65586.

    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589827] = ButtonA;
    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589826] = ButtonB;
    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589828] = ButtonX;
    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589825] = ButtonY;

    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589831] = LeftShoulder;
    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589832] = RightShoulder;
    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589829] = LeftShoulder2;
    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589830] = RightShoulder2;

    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589835] = Axis1Button;
    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589836] = Axis2Button;

    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589833] = ButtonSelect;
    // No center button
    _usageMapToInputEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][589834] = ButtonStart;

    //D-pad in red LED mode. In green LED mode, D-pad mimicks left stick axes.
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65593].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65593].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65593].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    //Left analog stick in red LED mode. In green LED mode, stick
    //mimicks digital signals & send only 0, 127, 255.
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));

    //Right analog stick in red LED mode. In green LED mode, stick
    //mimicks 1, 2, 3, & 4 buttons (Y, B, A, & X, respectively),
    //sending their IDs at up, down, left, and right.
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65586].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(DragonRiseID,SteelSeries3GCControllerID)][65589].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));


    // Amazon Fire Game Controller

    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][589825] = ButtonA;
    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][589826] = ButtonB;
    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][589828] = ButtonX;
    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][589829] = ButtonY;

    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][589832] = LeftShoulder;
    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][589831] = RightShoulder;
 
    _usageMapToInputRangeEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][131269].push_back(FSUSBElementInfoMap(-1,0,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][131268].push_back(FSUSBElementInfoMap(-1,0,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][589838] = Axis1Button;//L3
    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][589839] = Axis2Button;//R3

    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][589835] = ButtonSelect;//Android Back Button
    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][589837] = ButtonCenter;//GameCircle
    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][786979] = ButtonHome;//HomeButton
    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][589836] = ButtonStart;//Android Menu Button

    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][786612] = Button19;//Rewind button
    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][786637] = Button20;//Play Pause button
    _usageMapToInputEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][786611] = Button21;//Fast Forward button

    _usageMapToInputRangeEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][65593].push_back(FSUSBElementInfoMap(2,2,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][65593].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][65593].push_back(FSUSBElementInfoMap(6,6,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][65593].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][65593].push_back(FSUSBElementInfoMap(8,8,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(AmazonVendorID,AmazonFireGameControllerID)][65593].push_back(FSUSBElementInfoMap(0,0,LastValueUp,FSInputRest));

    // TODO: New mapping system for Fire TV controller anolog stick and trigger min and max of -1 to 0 is a lie.
    //_usageMapToInputRangeEvent[createId(AmazonVendorID,AmazonFireGameControllerID)][65584].push_back(FSUSBElementInfoMap(-1,0,XAxis,FSInputChanged));
    //_usageMapToInputRangeEvent[createId(AmazonVendorID,AmazonFireGameControllerID)][65585].push_back(FSUSBElementInfoMap(-1,0,YAxis,FSInputChanged));

    //_usageMapToInputRangeEvent[createId(AmazonVendorID,AmazonFireGameControllerID)][65586].push_back(FSUSBElementInfoMap(-1,0,XAxis2,FSInputChanged));
    //_usageMapToInputRangeEvent[createId(AmazonVendorID,AmazonFireGameControllerID)][65589].push_back(FSUSBElementInfoMap(-1,0,YAxis2,FSInputChanged));


    // Game Elements Recoil controller

    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589827] = ButtonA;
    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589826] = ButtonB;
    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589828] = ButtonX;
    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589825] = ButtonY;

    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589829] = LeftShoulder;
    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589830] = RightShoulder;
    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589831] = LeftShoulder2;
    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589832] = RightShoulder2;

    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589835] = Axis1Button;
    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589836] = Axis2Button;

    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589833] = ButtonSelect;
    // No center button
    _usageMapToInputEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][589834] = ButtonStart;

    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65593].push_back(FSUSBElementInfoMap(0,0,LastValueUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65593].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65593].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    //_usageMapToInputRangeEvent[createId(GameElementsVendorID,GameElementsRecoilID)][65593].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65586].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(GameElementsVendorID,GameElementsRecoilID)][65589].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));


    // SteelSeries Free controller

    _usageMapToInputEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][589825] = ButtonA;
    _usageMapToInputEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][589826] = ButtonB;
    _usageMapToInputEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][589828] = ButtonX;
    _usageMapToInputEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][589829] = ButtonY;

    _usageMapToInputEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][589831] = LeftShoulder;
    _usageMapToInputEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][589832] = RightShoulder;

    _usageMapToInputEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][589837] = ButtonSelect;//Labeled as "a"
    // No center button
    _usageMapToInputEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][589836] = ButtonStart;//Labeled as "b"

    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65593].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65593].push_back(FSUSBElementInfoMap(7,7,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65593].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65584].push_back(FSUSBElementInfoMap(-128,127,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65585].push_back(FSUSBElementInfoMap(-128,127,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65586].push_back(FSUSBElementInfoMap(-128,127,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(SteelSeriesVendorID,SteelSeriesFreeControllerID)][65589].push_back(FSUSBElementInfoMap(-128,127,YAxis2,FSInputChanged));


    // DualShock 3 Controller using macOS HIDIcookies

    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][21] = ButtonA;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][20] = ButtonB;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][19] = ButtonY;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][22] = ButtonX;

    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][17] = LeftShoulder;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][18] = RightShoulder;

    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][39].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][40].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][10] = ButtonStart;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][23] = ButtonCenter;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][7] = ButtonSelect;

    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][8] = Axis1Button;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][9] = Axis2Button;

    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][11] = DPadUp;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][12] = DPadRight;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][13] = DPadDown;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][14] = DPadLeft;

    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][27].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][26].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][28].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][29].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));

    // DualShock 3 Controller

    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589839] = ButtonA;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589838] = ButtonB;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589837] = ButtonY;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589840] = ButtonX;

    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589835] = LeftShoulder;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589836] = RightShoulder;

    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589834] = LeftShoulder2;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589833] = RightShoulder2;
   // _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589834].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
    //_usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589833].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589834].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589833].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger


    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589828] = ButtonStart;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589841] = ButtonCenter;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589825] = ButtonSelect;

    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589826] = Axis1Button;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589827] = Axis2Button;

    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589829] = DPadUp;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589830] = DPadRight;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589831] = DPadDown;
    _usageMapToInputEvent[createVPId(SonyVendorID,Playstation3ControllerID)][589832] = DPadLeft;

    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][65589].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][65586].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation3ControllerID)][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));

    // DualShock 4 Controller

    std::array<uint32_t,2> sonyProductIds{Playstation4ControllerIDV1,Playstation4ControllerIDV2};

    for ( auto Playstation4ControllerID : sonyProductIds)
    {
        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589826] = ButtonA;
        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589827] = ButtonB;
        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589828] = ButtonY;
        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589825] = ButtonX;

        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589829] = LeftShoulder;
        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589830] = RightShoulder;
        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589831] = LeftShoulder2;
        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589832] = RightShoulder2;

        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65587].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65588].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger

        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589835] = Axis1Button;
        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589836] = Axis2Button;

        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589833] = ButtonSelect;
        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589837] = ButtonCenter;
        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589838] = ButtonCenter;//button under touch pad

        _usageMapToInputEvent[createVPId(SonyVendorID,Playstation4ControllerID)][589834] = ButtonStart;

        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65593].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65593].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65593].push_back(FSUSBElementInfoMap(8,8,LastValueUp,FSInputRest));

        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));//LXaxis stick
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));//LYaxis stick
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65589].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));//RXaxis stick
        _usageMapToInputRangeEvent[createVPId(SonyVendorID,Playstation4ControllerID)][65586].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));//RYaxis stick
    }
    //Logitech F710

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589826] = ButtonA;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589827] = ButtonB;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589825] = ButtonX;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589828] = ButtonY;

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589829]= LeftShoulder;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589830] = RightShoulder;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589831] = LeftShoulder2;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589832] = RightShoulder2;

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589835] = Axis1Button;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589836] = Axis2Button;

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589833] = ButtonSelect;
    // No center button not accessible
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][589834] = ButtonStart;

    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65593].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65593].push_back(FSUSBElementInfoMap(5,5,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65593].push_back(FSUSBElementInfoMap(7,7,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65593].push_back(FSUSBElementInfoMap(8,8,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));//LXaxis stick
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));//LYaxis stick

    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65589].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));//RXaxis stick
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF710)][65586].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));//RYaxis stick


    // Logitech Dual Action

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589826] = ButtonA;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589827] = ButtonB;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589825] = ButtonX;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589828] = ButtonY;

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589829]= LeftShoulder;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589830] = RightShoulder;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589831] = LeftShoulder2;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589832] = RightShoulder2;

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589835] = Axis1Button;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589836] = Axis2Button;

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589833] = ButtonSelect;
    // No center button
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechDualActionID)][589834] = ButtonStart;

    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65593].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65593].push_back(FSUSBElementInfoMap(5,5,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65593].push_back(FSUSBElementInfoMap(7,7,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65593].push_back(FSUSBElementInfoMap(8,8,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));//LXaxis stick
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));//LYaxis stick

    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65589].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));//RXaxis stick
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechDualActionID)][65586].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));//RYaxis stick

    // Logitech Gamepad F310 in x mode

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589825] = ButtonA;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589826] = ButtonB;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589827] = ButtonX;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589828] = ButtonY;

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589829] = LeftShoulder;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589830] = RightShoulder;

    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][65586].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][65589].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589831] = Axis1Button;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589832] = Axis2Button;

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589834] = ButtonSelect;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589835] = ButtonCenter;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589833] = ButtonStart;

    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589836] = DPadUp;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589839] = DPadRight;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589837] = DPadDown;
    _usageMapToInputEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][589838] = DPadLeft;

    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][65584].push_back(FSUSBElementInfoMap(-32768,32767,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][65585].push_back(FSUSBElementInfoMap(-32768,32767,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][65587].push_back(FSUSBElementInfoMap(-32768,32767,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(LogitechVendorID,LogitechGamepadF310)][65588].push_back(FSUSBElementInfoMap(-32768,32767,YAxis2,FSInputChanged));

    // OUYA controller

    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589825] = ButtonA;
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589828] = ButtonB;
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589826] = ButtonX;
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589827] = ButtonY;

    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589829] = LeftShoulder;
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589830] = RightShoulder;
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589837] = LeftShoulder2;
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589838] = RightShoulder2;

    //_usageMapToInputRangeEvent[createId(OUYAVendorID,OUYAControllerID)][65586].push_back(FSUSBElementInfoMap(-1,0,Trigger1,FSInputChanged));
   // _usageMapToInputRangeEvent[createId(OUYAVendorID,OUYAControllerID)][65589].push_back(FSUSBElementInfoMap(-1,0,Trigger2,FSInputChanged));

    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589831] = Axis1Button;
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589832] = Axis2Button;

    // No SELECT button
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589839] = ButtonCenter;
    // No START button
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589831] = Axis1Button;//L3 left thumb down
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589832] = Axis2Button;//R3 right thumb down

    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589833] = DPadUp;
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589836] = DPadRight;
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589834] = DPadDown;
    _usageMapToInputEvent[createVPId(OUYAVendorID,OUYAControllerID)][589835] = DPadLeft;

    //_usageMapToInputRangeEvent[createId(OUYAVendorID,OUYAControllerID)][65584].push_back(FSUSBElementInfoMap(-1,0,XAxis,FSInputChanged));
    //_usageMapToInputRangeEvent[createId(OUYAVendorID,OUYAControllerID)][65585].push_back(FSUSBElementInfoMap(-1,0,YAxis,FSInputChanged));

    //_usageMapToInputRangeEvent[createId(OUYAVendorID,OUYAControllerID)][65587].push_back(FSUSBElementInfoMap(-1,0,XAxis2,FSInputChanged));
    //_usageMapToInputRangeEvent[createId(OUYAVendorID,OUYAControllerID)][65588].push_back(FSUSBElementInfoMap(-1,0,YAxis2,FSInputChanged));

    //gives back deltas instead of values
    //_usageMapToInputRangeEvent[createId(OUYAVendorID,OUYAControllerID)][65584].push_back(FSUSBElementInfoMap(-127,127,XAxis3,FSInputChanged));
   // _usageMapToInputRangeEvent[createId(OUYAVendorID,OUYAControllerID)][65585].push_back(FSUSBElementInfoMap(-127,127,YAxis3,FSInputChanged));

    // Microsoft Xbox 360 Windows controller
    std::array<uint32_t,2> microsoftProductIds{MicrosoftXbox360WindowsControllerID,MicrosoftXboxOneWindowsControllerID};

    for ( auto xboxControllerID : microsoftProductIds)
    {
        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589825] = ButtonA;
        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589826] = ButtonB;
        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589827] = ButtonX;
        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589828] = ButtonY;

        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589829] = LeftShoulder;//L1 sholder button
        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589830] = RightShoulder;//R2 sholder button

        //xbox 360 is for 0 - 255 but xbox one is for 0 - 1023 and the xbox one driver pretends it is a xbox 360 with the 1023 value
        _usageMapToInputRangeEvent[createVPId(MicrosoftVendorID,xboxControllerID)][65586].push_back(FSUSBElementInfoMap(0,1023,Trigger1,FSInputChanged));//L2 trigger
        _usageMapToInputRangeEvent[createVPId(MicrosoftVendorID,xboxControllerID)][65589].push_back(FSUSBElementInfoMap(0,1023,Trigger2,FSInputChanged));//R2 trigger

        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589831] = Axis1Button;//L3 left thumb down
        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589832] = Axis2Button;//R3 right thumb down

        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589834] = ButtonSelect;//back
        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589835] = ButtonCenter;//Microsoft xbox button
        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589840] = ButtonCenter;//Microsoft xbox one button

        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589833] = ButtonStart;//start

        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589836] = DPadUp;
        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589837] = DPadDown;
        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589838] = DPadLeft;
        _usageMapToInputEvent[createVPId(MicrosoftVendorID,xboxControllerID)][589839] = DPadRight;

        _usageMapToInputRangeEvent[createVPId(MicrosoftVendorID,xboxControllerID)][65584].push_back(FSUSBElementInfoMap(-32768,32767,XAxis,FSInputChanged));//LXaxis stick trigger
        _usageMapToInputRangeEvent[createVPId(MicrosoftVendorID,xboxControllerID)][65585].push_back(FSUSBElementInfoMap(-32768,32767,YAxis,FSInputChanged));//LYaxis stick trigger

        _usageMapToInputRangeEvent[createVPId(MicrosoftVendorID,xboxControllerID)][65587].push_back(FSUSBElementInfoMap(-32768,32767,XAxis2,FSInputChanged));//RXaxis stick trigger
        _usageMapToInputRangeEvent[createVPId(MicrosoftVendorID,xboxControllerID)][65588].push_back(FSUSBElementInfoMap(-32768,32767,YAxis2,FSInputChanged));//RYaxis stick trigger
    }

     //Rock candy xbox360 controller

    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589825] = ButtonA;
    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589826] = ButtonB;
    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589827] = ButtonX;
    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589828] = ButtonY;

    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589829] = LeftShoulder;//L1 sholder button
    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589830] = RightShoulder;//R2 sholder button
   //xbox 360 is for 0 - 255 but xbox one is for 0 - 1023 and the xbox one driver pretends it is a xbox 360 with the 1023 value
    _usageMapToInputRangeEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][65586].push_back(FSUSBElementInfoMap(0,1023,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][65589].push_back(FSUSBElementInfoMap(0,1023,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589831] = Axis1Button;//L3 left thumb down
    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589832] = Axis2Button;//R3 right thumb down

    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589834] = ButtonSelect;//back
    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589835] = ButtonCenter;//Microsoft xbox button
    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589840] = ButtonCenter;//Microsoft xbox one button

    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589833] = ButtonStart;//start

    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589836] = DPadUp;
    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589837] = DPadDown;
    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589838] = DPadLeft;
    _usageMapToInputEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][589839] = DPadRight;

    _usageMapToInputRangeEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][65584].push_back(FSUSBElementInfoMap(-32768,32767,XAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][65585].push_back(FSUSBElementInfoMap(-32768,32767,YAxis,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputRangeEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][65587].push_back(FSUSBElementInfoMap(-32768,32767,XAxis2,FSInputChanged));//RXaxis stick trigger
    _usageMapToInputRangeEvent[createVPId(RockCandyVendorID,RockCandyXbox360ControlllerID)][65588].push_back(FSUSBElementInfoMap(-32768,32767,YAxis2,FSInputChanged));//RYaxis stick trigger

    //Gravis GamePad Pro

    _usageMapToInputEvent[createVPId(GravisVendorID,GamePadProID)][589826] = ButtonA;
    _usageMapToInputEvent[createVPId(GravisVendorID,GamePadProID)][589827] = ButtonB ;
    _usageMapToInputEvent[createVPId(GravisVendorID,GamePadProID)][589825] = ButtonX;
    _usageMapToInputEvent[createVPId(GravisVendorID,GamePadProID)][589828] = ButtonY;

    _usageMapToInputEvent[createVPId(GravisVendorID,GamePadProID)][589829] = LeftShoulder;
    _usageMapToInputEvent[createVPId(GravisVendorID,GamePadProID)][589830] = RightShoulder;

    _usageMapToInputEvent[createVPId(GravisVendorID,GamePadProID)][589831] = LeftShoulder2;
    _usageMapToInputEvent[createVPId(GravisVendorID,GamePadProID)][589832] = RightShoulder2;

    _usageMapToInputEvent[createVPId(GravisVendorID,GamePadProID)][589833] = ButtonSelect;
    _usageMapToInputEvent[createVPId(GravisVendorID,GamePadProID)][589834] = ButtonStart;

    _usageMapToInputRangeEvent[createVPId(GravisVendorID,GamePadProID)][65585].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(GravisVendorID,GamePadProID)][65585].push_back(FSUSBElementInfoMap(255,255,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(GravisVendorID,GamePadProID)][65585].push_back(FSUSBElementInfoMap(127,127,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[createVPId(GravisVendorID,GamePadProID)][65584].push_back(FSUSBElementInfoMap(0,0,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(GravisVendorID,GamePadProID)][65584].push_back(FSUSBElementInfoMap(255,255,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(GravisVendorID,GamePadProID)][65584].push_back(FSUSBElementInfoMap(127,127,LastValueUp,FSInputRest));

    //ZD-V V Wired GamePad
    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65593].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65593].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65593].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589827] =  ButtonA;
    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589826] =  ButtonB;
    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589828] =  ButtonX;
    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589825] =  ButtonY;

    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589831] =  LeftShoulder2;
    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589832] =  RightShoulder2;
    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589829] =  LeftShoulder;
    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589830] =  RightShoulder;

    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589835] = Axis1Button;
    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589836] = Axis2Button;

    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589833] =  ButtonSelect;
    _usageMapToInputEvent[createVPId(ZDVVendorID,VWiredGamePadID)][589834] =  ButtonStart;

    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65589].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[createVPId(ZDVVendorID,VWiredGamePadID)][65586].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));

}

void FSUSBDeviceManager::init( )
{
    FSBaseManager::init();
}

FSUSBDeviceManager::~FSUSBDeviceManager()
{

}

void FSUSBDeviceManager::addMapping(unsigned int deviceID,unsigned int controlID,FSDeviceInput deviceInput)
{
    const FSUSBDevice * usbDeice = (const FSUSBDevice *)getDevice(deviceID);
    if(usbDeice != NULL)
    {
        vendorIDType vendorUSBID = static_cast<vendorIDType>(usbDeice->getVendorID());
        productIDType productUSBID = static_cast<productIDType>(usbDeice->getProductID());
        addMapping(vendorUSBID,productUSBID,controlID,deviceInput);
    }
}

void FSUSBDeviceManager::addMapping(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput)
{
    /** \todo
     *need to put into correct map based on min max
     */
    _usageMapToInputEvent[createVPId(vendorUSBID,productUSBID)][controlUSBID] = deviceInput;
}


/*FSUSBElementInfoMap  FSUSBDeviceManager::lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID)
{
    return FSUSBElementInfoMap(0,1,LastInput,FSInputChanged);
}*/


FSUSBElementInfoMap  FSUSBDeviceManager::lookUpDeviceInputFromID(idNumber deviceID, idNumber controlID, minMaxNumber min, minMaxNumber max, physicalValueNumber value)
{
    const FSUSBDevice * usbDeice = static_cast<const FSUSBDevice *>(getDevice(deviceID));
    if(usbDeice != NULL)
    {
        vendorIDType vendorUSBID = static_cast<vendorIDType>(usbDeice->getVendorID());
        productIDType productUSBID =static_cast<productIDType>(usbDeice->getProductID());
        return lookUpDeviceInputFromUSBID(vendorUSBID,
                                productUSBID ,
                                controlID,
                                min,
                                max,
                                value);

    }
    return FSUSBElementInfoMap(0,1,LastInput,FSInputChanged);
}

FSUSBElementInfoMap  FSUSBDeviceManager::lookUpDeviceInputFromUSBID( vendorIDType vendorUSBID, productIDType productUSBID , unsigned int controlID,minMaxNumber min,minMaxNumber max,int value,bool forceAnalogLookup)
 {
    deviceID vendorProductID = createVPId(vendorUSBID,productUSBID);
     if(min==0 && max == 1 && !forceAnalogLookup)
     {
         if(_usageMapToInputEvent.find(vendorProductID) != _usageMapToInputEvent.end() &&
                 _usageMapToInputEvent[vendorProductID].find(controlID) != _usageMapToInputEvent[vendorProductID].end())
         {
             FSEventAction isPressed = FSInputPressed;
             (value == 0 ) ? isPressed = FSInputRest: NULL;
             return FSUSBElementInfoMap(0,1,_usageMapToInputEvent[vendorProductID][controlID],isPressed);
         }
     }
     else
    {
         if(_usageMapToInputRangeEvent.find(vendorProductID) != _usageMapToInputRangeEvent.end() &&
                 _usageMapToInputRangeEvent[vendorProductID].find(controlID) != _usageMapToInputRangeEvent[vendorProductID].end())
        {
             for(std::vector<FSUSBElementInfoMap>::iterator rangeUsageList = _usageMapToInputRangeEvent[vendorProductID][controlID].begin(); rangeUsageList != _usageMapToInputRangeEvent[vendorProductID][controlID].end();++rangeUsageList)
             {
                 FSUSBElementInfoMap * item  = &(*rangeUsageList);
                 if(value >= item->getMin()  && value <= item->getMax())
                 {
                     return *item;
                 }
             }
         }
     }

    return FSUSBElementInfoMap(0,1,LastInput,FSInputChanged);
 }


bool FSUSBDeviceManager::doesElementHaveDeviceInputForValue(unsigned int vendorUSBID, unsigned int productUSBID ,unsigned int elementID,FSDeviceInput inputToLookFor )
{
   deviceID vendorProductID = createVPId(vendorUSBID,productUSBID);

   std::vector<FSUSBElementInfoMap> ::iterator itr =  _usageMapToInputRangeEvent[vendorProductID][elementID].begin();
   for(itr;itr !=  _usageMapToInputRangeEvent[vendorProductID][elementID].end(); ++itr)
   {
      FSUSBElementInfoMap infoMapToLookThrough = *itr;
      FSDeviceInput deviceInput = infoMapToLookThrough.getDeviceInput();
      if(deviceInput == inputToLookFor)
      {
          return true;
      }
   }
      return false;
}



bool FSUSBDeviceManager::doesDeviceHaveDeviceInputForValue(unsigned int deviceID,FSDeviceInput inputToLookFor,  int value )
{
    const FSUSBDevice * usbDeice = (const FSUSBDevice *)getDevice(deviceID);
    if(usbDeice != NULL)
    {
        vendorIDType vendorUSBID =static_cast<vendorIDType>(usbDeice->getVendorID());
        productIDType productUSBID = static_cast<productIDType>(usbDeice->getProductID());
        return  doesDeviceHaveDeviceInputForValue(vendorUSBID,productUSBID,inputToLookFor,value);
    }
    return false;
}


FSUSBElementInfoMap FSUSBDeviceManager::infoMapForInputType(vendorIDType vendorUSBID, productIDType productUSBID , FSDeviceInput inputToLookFor )
{
    deviceID vendorProductID = createVPId(vendorUSBID,productUSBID);
    std::unordered_map<idNumber,std::vector<FSUSBElementInfoMap> >::iterator itRange = _usageMapToInputRangeEvent[vendorProductID].begin();
    for(itRange;itRange != _usageMapToInputRangeEvent[vendorProductID].end();++itRange)
    {
       std::vector<FSUSBElementInfoMap>::iterator vItr = itRange->second.begin();
       for(vItr;vItr !=  itRange->second.end(); ++vItr)
       {
          FSUSBElementInfoMap infoMapToLookThrough = *vItr;
          if(infoMapToLookThrough.getDeviceInput() == inputToLookFor)
          {
              return infoMapToLookThrough;
          }
       }
    }
     FSUSBElementInfoMap temp(0,0,LastInput,FSLastEventAction);
    return temp;
}

bool FSUSBDeviceManager::doesDeviceHaveDeviceInputForValue(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor,  int value )
{
    deviceID vendorProductID = createVPId(vendorUSBID,productUSBID);
    std::unordered_map<idNumber,std::vector<FSUSBElementInfoMap> >::iterator itRange = _usageMapToInputRangeEvent[vendorProductID].begin();
    for(itRange;itRange != _usageMapToInputRangeEvent[vendorProductID].end();++itRange)
    {
       std::vector<FSUSBElementInfoMap>::iterator vItr = itRange->second.begin();
       for(vItr;vItr !=  itRange->second.end(); ++vItr)
       {
          FSUSBElementInfoMap infoMapToLookThrough = *vItr;
          if(infoMapToLookThrough.getDeviceInput() == inputToLookFor && value >= infoMapToLookThrough.getMin() && value <= infoMapToLookThrough.getMax())
          {
              return true;
          }
       }
    }
    return false;
}


bool FSUSBDeviceManager::doesDeviceHaveDeviceInput(unsigned int deviceID,FSDeviceInput inputToLookFor)
{
    const FSUSBDevice * usbDeice = (const FSUSBDevice *)getDevice(deviceID);
    if(usbDeice != NULL)
    {
        vendorIDType vendorUSBID = static_cast<vendorIDType>(usbDeice->getVendorID());
        productIDType productUSBID = static_cast<productIDType>(usbDeice->getProductID());
      return  doesDeviceHaveDeviceInput(vendorUSBID,productUSBID,inputToLookFor);
    }
    return false;
}



bool FSUSBDeviceManager::doesDeviceHaveDeviceInput(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor)
{
    static unsigned int  lastVendorUSBID = -1;
    static unsigned int  lastProductUSBID = -1;
    static FSDeviceInput lastInputToLookFor = Unknown;
    static bool lastResult = false;

    if(lastVendorUSBID == vendorUSBID && lastProductUSBID == productUSBID && lastInputToLookFor == inputToLookFor)
    {
        return lastResult;
    }

    lastVendorUSBID = vendorUSBID;
    lastProductUSBID = productUSBID;
    lastInputToLookFor = inputToLookFor;

    deviceID vendorProductID = createVPId(vendorUSBID,productUSBID);
    //TODO add this however right now there are no digital devices that use
    if(FS_isButtion(inputToLookFor) || FS_isDpad(inputToLookFor))
    {

        std::unordered_map<idNumber,FSDeviceInput>::iterator itDigital = _usageMapToInputEvent[vendorProductID].begin();
        for(itDigital; itDigital != _usageMapToInputEvent[vendorProductID].end() ; ++itDigital)
        {
            FSDeviceInput deviceInputFound = itDigital->second;
            if(deviceInputFound == inputToLookFor)
            {
                lastResult = true;
                return true;
            }
        }
        //look throught other
    }
    else
    {
        std::unordered_map<idNumber,std::vector<FSUSBElementInfoMap> >::iterator itRange = _usageMapToInputRangeEvent[vendorProductID].begin();
        for(itRange;itRange != _usageMapToInputRangeEvent[vendorProductID].end();++itRange)
        {
           std::vector<FSUSBElementInfoMap>::iterator vItr = itRange->second.begin();
           for(vItr;vItr !=  itRange->second.end(); ++vItr)
           {
              FSUSBElementInfoMap infoMapToLookThrough = *vItr;
              if(infoMapToLookThrough.getDeviceInput() == inputToLookFor)
              {
                  lastResult = true;
                  return true;
              }
           }
        }
    }

    lastResult = false;
    return false;
}
