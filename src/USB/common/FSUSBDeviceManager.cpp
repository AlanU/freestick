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
using namespace freestick;
FSUSBDeviceManager::FSUSBDeviceManager()
{
    /** \todo
    * populate map _usageMapToInputEvent
    */

    //First ps2 port
    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589827] =  ButtonA;
    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589826] =  ButtonB;
    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589828] =  ButtonY;
    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589825] =  ButtonX;

    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589831] =  LeftShoulder;
    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589832] =  RightShoulder;
    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589829] =  LeftShoulder2;
    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589830] =  RightShoulder2;

    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589835] = Axis1Button;
    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589836] = Axis2Button;

    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589833] =  ButtonSelect;
    _usageMapToInputEvent[HVG2VenderID][HVG2TwinPS2][589834] =  ButtonStart;

    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65593].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65593].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65593].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65589].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[HVG2VenderID][HVG2TwinPS2][65586].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));


    // SteelSeries ("DragonRise") 3GC controller
    // Has a very "noisy" analog axis ID 65586.

    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589827] = ButtonA;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589826] = ButtonB;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589828] = ButtonX;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589825] = ButtonY;

    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589831] = LeftShoulder;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589832] = RightShoulder;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589829] = LeftShoulder2;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589830] = RightShoulder2;

    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589835] = Axis1Button;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589836] = Axis2Button;

    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589833] = ButtonSelect;
    // No center button
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][589834] = ButtonStart;

    //D-pad in red LED mode. In green LED mode, D-pad mimicks left stick axes.
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65593].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65593].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65593].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    //Left analog stick in red LED mode. In green LED mode, stick
    //mimicks digital signals & send only 0, 127, 255.
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));

    //Right analog stick in red LED mode. In green LED mode, stick
    //mimicks 1, 2, 3, & 4 buttons (Y, B, A, & X, respectively),
    //sending their IDs at up, down, left, and right.
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65586].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][65589].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));


    // Amazon Fire Game Controller

    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][589825] = ButtonA;
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][589826] = ButtonB;
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][589828] = ButtonX;
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][589829] = ButtonY;

    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][589832] = LeftShoulder;
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][589831] = RightShoulder;
 
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][131269].push_back(FSUSBElementInfoMap(-1,0,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][131268].push_back(FSUSBElementInfoMap(-1,0,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][589838] = Axis1Button;//L3
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][589839] = Axis2Button;//R3

    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][589835] = ButtonSelect;//Android Back Button
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][589837] = ButtonCenter;//GameCircle
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][786979] = ButtonHome;//HomeButton
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][589836] = ButtonStart;//Android Menu Button

    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][786612] = Button19;//Rewind button
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][786637] = Button20;//Play Pause button
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][786611] = Button21;//Fast Forward button

    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65593].push_back(FSUSBElementInfoMap(2,2,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65593].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65593].push_back(FSUSBElementInfoMap(6,6,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65593].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65593].push_back(FSUSBElementInfoMap(8,8,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65593].push_back(FSUSBElementInfoMap(0,0,LastValueUp,FSInputRest));

    // TODO: New mapping system for Fire TV controller anolog stick and trigger min and max of -1 to 0 is a lie.
    //_usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65584].push_back(FSUSBElementInfoMap(-1,0,XAxis,FSInputChanged));
    //_usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65585].push_back(FSUSBElementInfoMap(-1,0,YAxis,FSInputChanged));

    //_usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65586].push_back(FSUSBElementInfoMap(-1,0,XAxis2,FSInputChanged));
    //_usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][65589].push_back(FSUSBElementInfoMap(-1,0,YAxis2,FSInputChanged));


    // Game Elements Recoil controller

    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589827] = ButtonA;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589826] = ButtonB;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589828] = ButtonX;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589825] = ButtonY;

    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589829] = LeftShoulder;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589830] = RightShoulder;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589831] = LeftShoulder2;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589832] = RightShoulder2;

    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589835] = Axis1Button;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589836] = Axis2Button;

    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589833] = ButtonSelect;
    // No center button
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][589834] = ButtonStart;

    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65593].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65593].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65593].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65586].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][65589].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));


    // SteelSeries Free controller

    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][589825] = ButtonA;
    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][589826] = ButtonB;
    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][589828] = ButtonX;
    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][589829] = ButtonY;

    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][589831] = LeftShoulder;
    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][589832] = RightShoulder;

    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][589837] = ButtonSelect;//Labeled as "a"
    // No center button
    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][589836] = ButtonStart;//Labeled as "b"

    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65593].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65593].push_back(FSUSBElementInfoMap(7,7,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65593].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65584].push_back(FSUSBElementInfoMap(-128,127,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65585].push_back(FSUSBElementInfoMap(-128,127,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65586].push_back(FSUSBElementInfoMap(-128,127,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][65589].push_back(FSUSBElementInfoMap(-128,127,YAxis2,FSInputChanged));


    // DualShock 3 Controller

    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][21] = ButtonA;
    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][20] = ButtonB;
    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][19] = ButtonY;
    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][22] = ButtonX;

    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][17] = LeftShoulder;
    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][18] = RightShoulder;

    _usageMapToInputRangeEvent[SonyVendorID][Playstation3ControllerID][39].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[SonyVendorID][Playstation3ControllerID][40].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][10] = ButtonStart;
    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][23] = ButtonCenter;
    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][7] = ButtonSelect;

    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][8] = Axis1Button;
    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][9] = Axis2Button;

    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][11] = DPadUp;
    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][12] = DPadRight;
    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][13] = DPadDown;
    _usageMapToInputEvent[SonyVendorID][Playstation3ControllerID][14] = DPadLeft;

    _usageMapToInputRangeEvent[SonyVendorID][Playstation3ControllerID][27].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation3ControllerID][26].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation3ControllerID][28].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation3ControllerID][29].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));

    // DualShock 4 Controller

    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589826] = ButtonA;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589827] = ButtonB;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589828] = ButtonY;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589825] = ButtonX;

    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589829] = LeftShoulder;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589830] = RightShoulder;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589831] = LeftShoulder2;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589832] = RightShoulder2;

    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65587].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65588].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589835] = Axis1Button;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589836] = Axis2Button;

    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589833] = ButtonSelect;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589837] = ButtonCenter;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589838] = ButtonCenter;//button under touch pad

    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][589834] = ButtonStart;

    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65593].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65593].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65593].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65593].push_back(FSUSBElementInfoMap(8,8,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));//LXaxis stick
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));//LYaxis stick
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65589].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));//RXaxis stick
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][65586].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));//RYaxis stick

    // Logitech Dual Action

    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589826] = ButtonA;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589827] = ButtonB;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589825] = ButtonX;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589828] = ButtonY;

    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589829]= LeftShoulder;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589830] = RightShoulder;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589831] = LeftShoulder2;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589832] = RightShoulder2;

    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589835] = Axis1Button;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589836] = Axis2Button;

    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589833] = ButtonSelect;
    // No center button
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][589834] = ButtonStart;

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65593].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65593].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65593].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65593].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65593].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65593].push_back(FSUSBElementInfoMap(5,5,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65593].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65593].push_back(FSUSBElementInfoMap(7,7,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65593].push_back(FSUSBElementInfoMap(8,8,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65584].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));//LXaxis stick
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65585].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));//LYaxis stick

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65589].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));//RXaxis stick
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][65586].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));//RYaxis stick

    // Logitech Gamepad F310 in x mode

    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589825] = ButtonA;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589828] = ButtonB;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589826] = ButtonX;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589827] = ButtonY;

    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589829] = LeftShoulder;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589830] = RightShoulder;

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][65586].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][65589].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));

    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589831] = Axis1Button;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589832] = Axis2Button;

    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589834] = ButtonSelect;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589835] = ButtonCenter;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589833] = ButtonStart;

    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589836] = DPadUp;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589839] = DPadRight;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589837] = DPadDown;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][589838] = DPadLeft;

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][65584].push_back(FSUSBElementInfoMap(-32768,32767,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][65585].push_back(FSUSBElementInfoMap(-32768,32767,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][65587].push_back(FSUSBElementInfoMap(-32768,32767,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][65588].push_back(FSUSBElementInfoMap(-32768,32767,YAxis2,FSInputChanged));

    // OUYA controller

    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589825] = ButtonA;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589828] = ButtonB;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589826] = ButtonX;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589827] = ButtonY;

    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589829] = LeftShoulder;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589830] = RightShoulder;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589837] = LeftShoulder2;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589838] = RightShoulder2;

    //_usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][65586].push_back(FSUSBElementInfoMap(-1,0,Trigger1,FSInputChanged));
   // _usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][65589].push_back(FSUSBElementInfoMap(-1,0,Trigger2,FSInputChanged));

    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589831] = Axis1Button;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589832] = Axis2Button;

    // No SELECT button
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589839] = ButtonCenter;
    // No START button
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589831] = Axis1Button;//L3 left thumb down
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589832] = Axis2Button;//R3 right thumb down

    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589833] = DPadUp;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589836] = DPadRight;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589834] = DPadDown;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][589835] = DPadLeft;

    //_usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][65584].push_back(FSUSBElementInfoMap(-1,0,XAxis,FSInputChanged));
    //_usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][65585].push_back(FSUSBElementInfoMap(-1,0,YAxis,FSInputChanged));

    //_usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][65587].push_back(FSUSBElementInfoMap(-1,0,XAxis2,FSInputChanged));
    //_usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][65588].push_back(FSUSBElementInfoMap(-1,0,YAxis2,FSInputChanged));

    //gives back deltas instead of values
    //_usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][65584].push_back(FSUSBElementInfoMap(-127,127,XAxis3,FSInputChanged));
   // _usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][65585].push_back(FSUSBElementInfoMap(-127,127,YAxis3,FSInputChanged));

    // Microsoft Xbox 360 Windows controller

    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589825] = ButtonA;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589826] = ButtonB;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589827] = ButtonX;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589828] = ButtonY;

    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589829] = LeftShoulder;//L1 sholder button
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589830] = RightShoulder;//R2 sholder button

    //xbox 360 is for 0 - 255 but xbox one is for 0 - 1023 and the xbox one driver pretends it is a xbox 360 with the 1023 value
    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][65586].push_back(FSUSBElementInfoMap(0,1023,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][65589].push_back(FSUSBElementInfoMap(0,1023,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589831] = Axis1Button;//L3 left thumb down
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589832] = Axis2Button;//R3 right thumb down

    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589834] = ButtonSelect;//back
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589835] = ButtonCenter;//Microsoft xbox button
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589840] = ButtonCenter;//Microsoft xbox one button

    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589833] = ButtonStart;//start

    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589836] = DPadUp;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589837] = DPadDown;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589838] = DPadLeft;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][589839] = DPadRight;

    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][65584].push_back(FSUSBElementInfoMap(-32768,32767,XAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][65585].push_back(FSUSBElementInfoMap(-32768,32767,YAxis,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][65587].push_back(FSUSBElementInfoMap(-32768,32767,XAxis2,FSInputChanged));//RXaxis stick trigger
    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][65588].push_back(FSUSBElementInfoMap(-32768,32767,YAxis2,FSInputChanged));//RYaxis stick trigger


     //Rock candy xbox360 controller

    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589825] = ButtonA;
    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589826] = ButtonB;
    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589827] = ButtonX;
    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589828] = ButtonY;

    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589829] = LeftShoulder;//L1 sholder button
    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589830] = RightShoulder;//R2 sholder button
   //xbox 360 is for 0 - 255 but xbox one is for 0 - 1023 and the xbox one driver pretends it is a xbox 360 with the 1023 value
    _usageMapToInputRangeEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][65586].push_back(FSUSBElementInfoMap(0,1023,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][65589].push_back(FSUSBElementInfoMap(0,1023,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589831] = Axis1Button;//L3 left thumb down
    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589832] = Axis2Button;//R3 right thumb down

    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589834] = ButtonSelect;//back
    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589835] = ButtonCenter;//Microsoft xbox button
    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589840] = ButtonCenter;//Microsoft xbox one button

    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589833] = ButtonStart;//start

    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589836] = DPadUp;
    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589837] = DPadDown;
    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589838] = DPadLeft;
    _usageMapToInputEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][589839] = DPadRight;

    _usageMapToInputRangeEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][65584].push_back(FSUSBElementInfoMap(-32768,32767,XAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][65585].push_back(FSUSBElementInfoMap(-32768,32767,YAxis,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputRangeEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][65587].push_back(FSUSBElementInfoMap(-32768,32767,XAxis2,FSInputChanged));//RXaxis stick trigger
    _usageMapToInputRangeEvent[RockCandyVenderID][RockCandyXbox360ControlllerID][65588].push_back(FSUSBElementInfoMap(-32768,32767,YAxis2,FSInputChanged));//RYaxis stick trigger



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
        unsigned int vendorUSBID = usbDeice->getVenderID();
        unsigned int productUSBID = usbDeice->getProductID();
        addMapping(vendorUSBID,productUSBID,controlID,deviceInput);
    }
}

void FSUSBDeviceManager::addMapping(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput)
{
    /** \todo
     *need to put into correct map based on min max
     */
    _usageMapToInputEvent[vendorUSBID][productUSBID][controlUSBID] = deviceInput;
}


/*FSUSBElementInfoMap  FSUSBDeviceManager::lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID)
{
    return FSUSBElementInfoMap(0,1,LastInput,FSInputChanged);
}*/


FSUSBElementInfoMap  FSUSBDeviceManager::lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID,signed long min,signed long max,int value)
{
    const FSUSBDevice * usbDeice = (const FSUSBDevice *)getDevice(deviceID);
    if(usbDeice != NULL)
    {
        unsigned int vendorUSBID = usbDeice->getVenderID();
        unsigned int productUSBID = usbDeice->getProductID();
        return lookUpDeviceInputFromUSBID(vendorUSBID,
                                productUSBID ,
                                controlID,
                                min,
                                max,
                                value);

    }
    return FSUSBElementInfoMap(0,1,LastInput,FSInputChanged);
}

FSUSBElementInfoMap  FSUSBDeviceManager::lookUpDeviceInputFromUSBID( unsigned int vendorUSBID, unsigned int productUSBID , unsigned int controlID,signed long min,signed long max,int value)
 {
     if(min==0 && max == 1)
     {
         if(_usageMapToInputEvent.find(vendorUSBID) != _usageMapToInputEvent.end() &&
                 _usageMapToInputEvent[vendorUSBID].find(productUSBID) != _usageMapToInputEvent[vendorUSBID].end() &&
                 _usageMapToInputEvent[vendorUSBID][productUSBID].find(controlID) != _usageMapToInputEvent[vendorUSBID][productUSBID].end())
         {
             FSEventAction isPressed = FSInputPressed;
             (value == 0 ) ? isPressed = FSInputRest: NULL;
             return FSUSBElementInfoMap(0,1,_usageMapToInputEvent[vendorUSBID][productUSBID][controlID],isPressed);
         }
     }
     else
    {
         if(_usageMapToInputRangeEvent.find(vendorUSBID) != _usageMapToInputRangeEvent.end() &&
                  _usageMapToInputRangeEvent[vendorUSBID].find(productUSBID) != _usageMapToInputRangeEvent[vendorUSBID].end() &&
                 _usageMapToInputRangeEvent[vendorUSBID][productUSBID].find(controlID) != _usageMapToInputRangeEvent[vendorUSBID][productUSBID].end())
        {
             std::vector<FSUSBElementInfoMap>::iterator rangeUsageList = _usageMapToInputRangeEvent[vendorUSBID][productUSBID][controlID].begin();
             for(rangeUsageList; rangeUsageList != _usageMapToInputRangeEvent[vendorUSBID][productUSBID][controlID].end();rangeUsageList++)
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
   std::vector<FSUSBElementInfoMap> ::iterator itr =  _usageMapToInputRangeEvent[vendorUSBID][productUSBID][elementID].begin();
   for(itr;itr !=  _usageMapToInputRangeEvent[vendorUSBID][productUSBID][elementID].end(); itr++)
   {
      FSUSBElementInfoMap infoMapToLookThrough = *itr;
      if(infoMapToLookThrough.getDeviceInput() == inputToLookFor)
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
        unsigned int vendorUSBID = usbDeice->getVenderID();
        unsigned int productUSBID = usbDeice->getProductID();
        doesDeviceHaveDeviceInputForValue(vendorUSBID,productUSBID,inputToLookFor,value);
    }
}


bool FSUSBDeviceManager::doesDeviceHaveDeviceInputForValue(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor,  int value )
{
    std::map<IDNumber,std::vector<FSUSBElementInfoMap> >::iterator itRange = _usageMapToInputRangeEvent[vendorUSBID][productUSBID].begin();
    for(itRange;itRange != _usageMapToInputRangeEvent[vendorUSBID][productUSBID].end();itRange++)
    {
       std::vector<FSUSBElementInfoMap>::iterator vItr = itRange->second.begin();
       for(vItr;vItr !=  itRange->second.end(); vItr++)
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
        unsigned int vendorUSBID = usbDeice->getVenderID();
        unsigned int productUSBID = usbDeice->getProductID();
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
    //TODO add this however right now there are no digital devices that use
    if(FS_isButtion(inputToLookFor) || FS_isDpad(inputToLookFor))
    {

        std::map<IDNumber,FSDeviceInput>::iterator itDigital = _usageMapToInputEvent[vendorUSBID][productUSBID].begin();
        for(itDigital; itDigital != _usageMapToInputEvent[vendorUSBID][productUSBID].end() ; itDigital++)
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
        std::map<IDNumber,std::vector<FSUSBElementInfoMap> >::iterator itRange = _usageMapToInputRangeEvent[vendorUSBID][productUSBID].begin();
        for(itRange;itRange != _usageMapToInputRangeEvent[vendorUSBID][productUSBID].end();itRange++)
        {
           std::vector<FSUSBElementInfoMap>::iterator vItr = itRange->second.begin();
           for(vItr;vItr !=  itRange->second.end(); vItr++)
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
