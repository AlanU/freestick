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


    const unsigned int AmazonVenderID = 6473;
    const unsigned int AmazonFireGameControllerID = 1026 ;

    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][9] = ButtonX;
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][10] = ButtonY;
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][6] = ButtonA;
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][7] = ButtonB;


    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][16] = ButtonSelect;
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][17] = ButtonStart;
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][13] = RightShoulder;
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][12] = LeftShoulder;
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][19] = Axis1Button;//L3
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][20] = Axis2Button;//R3
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][18] = ButtonCenter;//GameCircle

    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][25] = ButtonHome;//HomeButton

    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][17] = Button18;//Menu button
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][23] = Button19;//Rewind button
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][24] = Button20;//Play Pause button
    _usageMapToInputEvent[AmazonVenderID][AmazonFireGameControllerID][22] = Button21;//Fast Forward button

    _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][34].push_back(FSUSBElementInfoMap(-1,0,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][35].push_back(FSUSBElementInfoMap(-1,0,Trigger2,FSInputChanged));//R2 trigger


    _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(2,2,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(6,6,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(8,8,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][36].push_back(FSUSBElementInfoMap(0,0,LastValueUp,FSInputRest));

     //TODO new mapping system for fire tv controller anolog stick and trigger min and max of -1 to 0 is a lie
    //_usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][31].push_back(FSUSBElementInfoMap(-1,0,YAxis,FSInputChanged));
    //_usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][30].push_back(FSUSBElementInfoMap(-1,0,XAxis,FSInputChanged));

    //_usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][33].push_back(FSUSBElementInfoMap(-1,0,YAxis2,FSInputChanged));
   // _usageMapToInputRangeEvent[AmazonVenderID][AmazonFireGameControllerID][32].push_back(FSUSBElementInfoMap(-1,0,XAxis2,FSInputChanged));




    const unsigned int GameElementsVenderID = 3888;
    const unsigned int GameElementRecoilID = 263;
    
    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][6] = ButtonX;
    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][3] = ButtonY;
    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][5] = ButtonA;
    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][4] = ButtonB;
    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][11] = ButtonSelect;
    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][12] = ButtonStart;
    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][8] = RightShoulder;
    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][7] = LeftShoulder;
    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][13] = Axis1Button;//L3
    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][14] = Axis2Button;//R3

    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][10] = RightShoulder2;
    _usageMapToInputEvent[GameElementsVenderID][GameElementRecoilID][9] = LeftShoulder2;


    
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][19].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][19].push_back(FSUSBElementInfoMap(2,2,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][19].push_back(FSUSBElementInfoMap(3,3,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][19].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][19].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][19].push_back(FSUSBElementInfoMap(6,6,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][19].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][19].push_back(FSUSBElementInfoMap(8,8,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][19].push_back(FSUSBElementInfoMap(0,0,LastValueUp,FSInputRest));
    
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][16].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][15].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][17].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[GameElementsVenderID][GameElementRecoilID][18].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));

   

    


    const unsigned int SteelSeriesVenderID = 4152;
    const unsigned int SteelSeriesFreeControllerID = 5138;

    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][20].push_back(FSUSBElementInfoMap(-128,127,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][21].push_back(FSUSBElementInfoMap(-128,127,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][22].push_back(FSUSBElementInfoMap(-128,127,XAxis2,FSInputChanged));
    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][23].push_back(FSUSBElementInfoMap(-128,127,YAxis2,FSInputChanged));

    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(1,1,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(5,5,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(7,7,DPadUp,FSInputPressed));

    _usageMapToInputRangeEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][19].push_back(FSUSBElementInfoMap(15,15,LastValueUp,FSInputRest));

    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][6] = Button1;
    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][7] = Button2;
    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][4] = Button3;
    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][3] = Button4;
    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][15] = ButtonA;//a
    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][14] = ButtonB;//b
    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][9] = LeftShoulder;//left trigger
    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][10] = RightShoulder;//right trigger


    //" Playstation 3 Controller"
    const unsigned int SonyVenderID = 1356;
    const unsigned int Playstation3ControllerID = 616;

    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][11] = DPadUp;
    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][13] = DPadDown;
    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][14] = DPadLeft;
    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][12] = DPadRight;

    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][19] = ButtonY;
    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][22] = ButtonX;
    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][21] = ButtonA;
    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][20] = ButtonB;

    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][10] = ButtonStart;
    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][7] = ButtonSelect;
    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][23] = ButtonCenter;

    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][17] = LeftShoulder;
    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][18] = RightShoulder;

    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][8] = Axis1Button;
    _usageMapToInputEvent[SonyVenderID][Playstation3ControllerID][9] = Axis2Button;


    _usageMapToInputRangeEvent[SonyVenderID][Playstation3ControllerID][39].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[SonyVenderID][Playstation3ControllerID][40].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputRangeEvent[SonyVenderID][Playstation3ControllerID][27].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));
    _usageMapToInputRangeEvent[SonyVenderID][Playstation3ControllerID][26].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));

    _usageMapToInputRangeEvent[SonyVenderID][Playstation3ControllerID][28].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));
    _usageMapToInputRangeEvent[SonyVenderID][Playstation3ControllerID][29].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));//LYaxis stick trigger

    const unsigned int Playstation4ControllerID = 1476;

    _usageMapToInputEvent[SonyVenderID][Playstation4ControllerID][5] = ButtonY;
    _usageMapToInputEvent[SonyVenderID][Playstation4ControllerID][2] = ButtonX;
    _usageMapToInputEvent[SonyVenderID][Playstation4ControllerID][3] = ButtonA;
    _usageMapToInputEvent[SonyVenderID][Playstation4ControllerID][4] = ButtonB;

    _usageMapToInputEvent[SonyVenderID][Playstation4ControllerID][7] = RightShoulder;
    _usageMapToInputEvent[SonyVenderID][Playstation4ControllerID][6] = LeftShoulder;
    _usageMapToInputEvent[SonyVenderID][Playstation4ControllerID][8] = LeftShoulder2;
    _usageMapToInputEvent[SonyVenderID][Playstation4ControllerID][9] = RightShoulder2;

    _usageMapToInputEvent[SonyVenderID][Playstation4ControllerID][10] = ButtonSelect;
    _usageMapToInputEvent[SonyVenderID][Playstation4ControllerID][11] = ButtonStart;
    _usageMapToInputEvent[SonyVenderID][Playstation4ControllerID][14] = ButtonCenter;

    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][21].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][22].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));

    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(7,7,DPadLeft,FSInputPressed));

    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][20].push_back(FSUSBElementInfoMap(8,8,LastValueUp,FSInputRest));


    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][16].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][17].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][19].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[SonyVenderID][Playstation4ControllerID][18].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));//LYaxis stick trigger

    // "Logitech Dual Action"
    const unsigned int LogitchVenderID = 1133;
    const unsigned int LogitchDualActionID = 49686;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][4] = ButtonX;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][5] = ButtonA;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][6] = ButtonB;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][7] = ButtonY;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][8]= LeftShoulder;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][9] = RightShoulder;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][10] = LeftShoulder2;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][11] = RightShoulder2;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][12] = ButtonSelect;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][13] = ButtonStart;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][14] = Axis1Button;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][15] = Axis2Button;


    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(7,7,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(8,8,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][16].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][17].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][19].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][18].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));//LYaxis stick trigger


    const unsigned int MicrosoftVentderID = 1118;
    const unsigned int MictrosftXbox360WindowsControllerID = 654;

    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][23] = ButtonX;//x
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][24] = ButtonY;//y
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][22] = ButtonB;//b
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][21] = ButtonA;//a

    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][16] = Axis1Button;//L3 left thumb down
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][17] = Axis2Button;//R3 right thumb down

    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][15] = ButtonSelect;//back
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][20] = ButtonCenter;//Microsoft xbox button
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][14] = ButtonStart;//start



    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][25].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][26].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][27].push_back(FSUSBElementInfoMap(-32768,32767,XAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][28].push_back(FSUSBElementInfoMap(-32768,32767,YAxis,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][29].push_back(FSUSBElementInfoMap(-32768,32767,XAxis2,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][30].push_back(FSUSBElementInfoMap(-32768,32767,YAxis2,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][18] = LeftShoulder;//L1 sholder button
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][19] = RightShoulder;//R2 sholder button
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][10] = DPadUp;
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][11] = DPadDown;
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][12] = DPadLeft;
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][13] = DPadRight;
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
