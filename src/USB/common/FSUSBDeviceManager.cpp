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
#include <algorithm>
using namespace freestick;
FSUSBDeviceManager::FSUSBDeviceManager()
{
    /** \todo
    * populate map _usageMapToInputEvent
    */

    // SteelSeries ("DragonRise") 3GC controller
    const unsigned int DragonRiseID = 121;
    const unsigned int SteelSeries3GCControllerID = 6;

    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][6] = ButtonA;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][5] = ButtonB;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][7] = ButtonX;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][4] = ButtonY;

    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][10] = LeftShoulder;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][11] = RightShoulder;

    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][8] = LeftShoulder2;
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][9] = RightShoulder2;

    // No stick buttons

    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][12] = ButtonSelect;
    // No center button
    _usageMapToInputEvent[DragonRiseID][SteelSeries3GCControllerID][13] = ButtonStart;

    //Dpad in green led mode
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][36].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][36].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][36].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][36].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][36].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][36].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][36].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][36].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][36].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    //Dpad in red led mode
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][22].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][22].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][22].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][22].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][22].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][22].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][22].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][22].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][22].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][17].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][18].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));

    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][19].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[DragonRiseID][SteelSeries3GCControllerID][20].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));

    // Amazon Fire Game Controller
    const unsigned int AmazonVendorID = 6473;
    const unsigned int AmazonFireGameControllerID = 1026 ;

    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][6] = ButtonA;
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][7] = ButtonB;
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][9] = ButtonX;
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][10] = ButtonY;

    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][13] = RightShoulder;
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][12] = LeftShoulder;

    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][34].push_back(FSUSBElementInfoMap(-1,0,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][35].push_back(FSUSBElementInfoMap(-1,0,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][19] = Axis1Button;//L3
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][20] = Axis2Button;//R3

    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][16] = ButtonSelect;
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][18] = ButtonCenter;//GameCircle
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][25] = ButtonHome;//HomeButton
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][17] = ButtonStart;

    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][23] = Button19;//Rewind button
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][24] = Button20;//Play Pause button
    _usageMapToInputEvent[AmazonVendorID][AmazonFireGameControllerID][22] = Button21;//Fast Forward button

    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(2,2,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(6,6,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(8,8,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(0,0,LastValueUp,FSInputRest));

    //TODO: New mapping system for Fire TV controller anolog stick and trigger min and max of -1 to 0 is a lie.
    //_usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][31].push_back(FSUSBElementInfoMap(-1,0,YAxis,FSInputChanged));
    //_usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][30].push_back(FSUSBElementInfoMap(-1,0,XAxis,FSInputChanged));

    //_usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][33].push_back(FSUSBElementInfoMap(-1,0,YAxis2,FSInputChanged));
    // _usageMapToInputRangeEvent[AmazonVendorID][AmazonFireGameControllerID][32].push_back(FSUSBElementInfoMap(-1,0,XAxis2,FSInputChanged));

    // Game Elements Recoil controller
    const unsigned int GameElementsVendorID = 3888;
    const unsigned int GameElementsRecoilID = 263;
    
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][5] = ButtonA;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][4] = ButtonB;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][6] = ButtonX;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][3] = ButtonY;

    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][7] = LeftShoulder;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][8] = RightShoulder;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][9] = LeftShoulder2;
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][10] = RightShoulder2;

    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][13] = Axis1Button;//L3
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][14] = Axis2Button;//R3

    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][11] = ButtonSelect;
    // No center button
    _usageMapToInputEvent[GameElementsVendorID][GameElementsRecoilID][12] = ButtonStart;
    
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][19].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][19].push_back(FSUSBElementInfoMap(2,2,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][19].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][19].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][19].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][19].push_back(FSUSBElementInfoMap(6,6,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][19].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][19].push_back(FSUSBElementInfoMap(8,8,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][19].push_back(FSUSBElementInfoMap(0,0,LastValueUp,FSInputRest));
    
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][16].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][15].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][17].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[GameElementsVendorID][GameElementsRecoilID][18].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));

    // SteelSeries Free controller
    const unsigned int SteelSeriesVendorID = 4152;
    const unsigned int SteelSeriesFreeControllerID = 5138;

    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][4] = ButtonB;
    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][3] = ButtonA;
    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][6] = ButtonX;
    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][7] = ButtonY;

    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][9] = LeftShoulder;
    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][10] = RightShoulder;

    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][15] = ButtonSelect;//Labeled as "a"
    // No center button
    _usageMapToInputEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][14] = ButtonStart;//Labeled as "b"

    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(7,7,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][20].push_back(FSUSBElementInfoMap(-128,127,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][21].push_back(FSUSBElementInfoMap(-128,127,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][22].push_back(FSUSBElementInfoMap(-128,127,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[SteelSeriesVendorID][SteelSeriesFreeControllerID][23].push_back(FSUSBElementInfoMap(-128,127,YAxis2,FSInputChanged));

    // DualShock 3 Controller
    const unsigned int SonyVendorID = 1356;
    const unsigned int Playstation3ControllerID = 616;

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

    _usageMapToInputRangeEvent[SonyVendorID][Playstation3ControllerID][27].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation3ControllerID][26].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation3ControllerID][28].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation3ControllerID][29].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));

    // DualShock 4 Controller
    const unsigned int Playstation4ControllerID = 1476;

    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][3] = ButtonA;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][4] = ButtonB;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][5] = ButtonY;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][2] = ButtonX;

    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][6] = LeftShoulder;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][7] = RightShoulder;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][8] = LeftShoulder2;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][9] = RightShoulder2;

    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][21].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][22].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][12] = Axis1Button;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][13] = Axis2Button;

    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][10] = ButtonSelect;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][14] = ButtonCenter;
    _usageMapToInputEvent[SonyVendorID][Playstation4ControllerID][11] = ButtonStart;

    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(8,8,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][16].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));//LXaxis stick
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][17].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));//LYaxis stick
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][19].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));//RXaxis stick
    _usageMapToInputRangeEvent[SonyVendorID][Playstation4ControllerID][18].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));//RYaxis stick

    // Logitech Dual Action
    const unsigned int LogitechVendorID = 1133;
    const unsigned int LogitechDualActionID = 49686;

    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][5] = ButtonA;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][6] = ButtonB;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][4] = ButtonX;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][7] = ButtonY;

    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][8]= LeftShoulder;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][9] = RightShoulder;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][10] = LeftShoulder2;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][11] = RightShoulder2;

    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][14] = Axis1Button;
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][15] = Axis2Button;

    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][12] = ButtonSelect;
    // No center button
    _usageMapToInputEvent[LogitechVendorID][LogitechDualActionID][13] = ButtonStart;

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][20].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][20].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][20].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][20].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][20].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][20].push_back(FSUSBElementInfoMap(5,5,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][20].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][20].push_back(FSUSBElementInfoMap(7,7,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][20].push_back(FSUSBElementInfoMap(8,8,LastValueUp,FSInputRest));

    // Actually for DirectInput mode of Logitech Gamepad F310
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][21].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][21].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][21].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][21].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][21].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][21].push_back(FSUSBElementInfoMap(7,7,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][21].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][21].push_back(FSUSBElementInfoMap(8,8,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][16].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));//LXaxis stick
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][17].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));//LYaxis stick

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][19].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));//RXaxis stick
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechDualActionID][18].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));//RYaxis stick

    // Logitech Gamepad F310
    const unsigned int LogitechGamepadF310 = 49693;

    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][21] = ButtonA;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][22] = ButtonB;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][23] = ButtonX;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][24] = ButtonY;

    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][18] = LeftShoulder;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][19] = RightShoulder;

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][25].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][26].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));

    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][16] = Axis1Button;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][17] = Axis2Button;

    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][15] = ButtonSelect;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][20] = ButtonCenter;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][14] = ButtonStart;

    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][10] = DPadUp;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][13] = DPadRight;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][11] = DPadDown;
    _usageMapToInputEvent[LogitechVendorID][LogitechGamepadF310][12] = DPadLeft;

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][27].push_back(FSUSBElementInfoMap(-32768,32767,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][28].push_back(FSUSBElementInfoMap(-32768,32767,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][29].push_back(FSUSBElementInfoMap(-32768,32767,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[LogitechVendorID][LogitechGamepadF310][30].push_back(FSUSBElementInfoMap(-32768,32767,YAxis2,FSInputChanged));

    // OUYA controller
    const unsigned int OUYAVendorID = 10294;
    const unsigned int OUYAControllerID = 1; // heh.

    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][15] = ButtonA;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][18] = ButtonB;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][16] = ButtonX;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][17] = ButtonY;

    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][19] = LeftShoulder;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][20] = RightShoulder;

    //TODO: OUYA triggers not mappable yet.
    // _usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][38].push_back(FSUSBElementInfoMap(-32768,32767,Trigger1,FSInputChanged));
    // _usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][39].push_back(FSUSBElementInfoMap(-32768,32767,Trigger2,FSInputChanged));

    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][21] = Axis1Button;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][22] = Axis2Button;

    // No SELECT button
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][29] = ButtonCenter;
    // No START button

    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][23] = DPadUp;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][26] = DPadRight;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][24] = DPadDown;
    _usageMapToInputEvent[OUYAVendorID][OUYAControllerID][25] = DPadLeft;

    _usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][34].push_back(FSUSBElementInfoMap(-32768,32767,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][35].push_back(FSUSBElementInfoMap(-32768,32767,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][36].push_back(FSUSBElementInfoMap(-32768,32767,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[OUYAVendorID][OUYAControllerID][37].push_back(FSUSBElementInfoMap(-32768,32767,YAxis2,FSInputChanged));

    // Microsoft Xbox 360 Windows controller
    const unsigned int MicrosoftVendorID = 1118;
    const unsigned int MicrosoftXbox360WindowsControllerID = 654;

    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][21] = ButtonA;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][22] = ButtonB;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][23] = ButtonX;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][24] = ButtonY;

    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][18] = LeftShoulder;//L1 sholder button
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][19] = RightShoulder;//R2 sholder button

    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][25].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][26].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][16] = Axis1Button;//L3 left thumb down
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][17] = Axis2Button;//R3 right thumb down

    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][15] = ButtonSelect;//back
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][20] = ButtonCenter;//Microsoft xbox button
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][14] = ButtonStart;//start

    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][10] = DPadUp;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][11] = DPadDown;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][12] = DPadLeft;
    _usageMapToInputEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][13] = DPadRight;

    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][27].push_back(FSUSBElementInfoMap(-32768,32767,XAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][28].push_back(FSUSBElementInfoMap(-32768,32767,YAxis,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][29].push_back(FSUSBElementInfoMap(-32768,32767,XAxis2,FSInputChanged));//RXaxis stick trigger
    _usageMapToInputRangeEvent[MicrosoftVendorID][MicrosoftXbox360WindowsControllerID][30].push_back(FSUSBElementInfoMap(-32768,32767,YAxis2,FSInputChanged));//RYaxis stick trigger
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
