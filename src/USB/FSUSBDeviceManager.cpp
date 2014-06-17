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

#include "FSUSBDeviceManager.h"
#include "../baseClasses/FSBaseManager.h"
#include "../USB/FSUSBDevice.h"
#include <algorithm>
using namespace freestick;
FSUSBDeviceManager::FSUSBDeviceManager()
{
    /** \todo
    * populate map _usageMapToInputEvent
    */

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
    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][15] = Button5;//a
    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][14] = Button6;//b
    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][9] = Button5;//left trigger
    _usageMapToInputEvent[SteelSeriesVenderID][SteelSeriesFreeControllerID][10] = Button6;//right trigger


    //" Playstation 3 Controller"
    const unsigned int SonyVenderID = 1356;
    const unsigned int Playstation3ControllerID = 616;


    // "Logitech Dual Action"
    const unsigned int LogitchVenderID = 1133;
    const unsigned int LogitchDualActionID = 49686;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][4] = Button1;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][5] = Button2;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][6] = Button3;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][7] = Button4;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][8]= Button5;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][9] = Button6;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][10] = Button7;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][11] = Button8;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][12] = Button9;
    _usageMapToInputEvent[LogitchVenderID][LogitchDualActionID][13] = Button10;

    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(0,0,DPadUp,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(2,2,DPadRight,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(4,4,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(3,3,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(7,7,DPadDown,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(6,6,DPadLeft,FSInputPressed));
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][20].push_back(FSUSBElementInfoMap(8,8,LastValueUp,FSInputRest));

    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][16].push_back(FSUSBElementInfoMap(0,255,XAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][17].push_back(FSUSBElementInfoMap(0,255,YAxis,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][19].push_back(FSUSBElementInfoMap(0,255,XAxis2,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[LogitchVenderID][LogitchDualActionID][18].push_back(FSUSBElementInfoMap(0,255,YAxis2,FSInputChanged));//LYaxis stick trigger


    const unsigned int MicrosoftVentderID = 1118;
    const unsigned int MictrosftXbox360WindowsControllerID = 654;

    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][23] = Button1;//x
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][24] = Button2;//y
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][22] = Button3;//b
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][21] = Button4;//a

    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][16] = Button5;//L3 left thumb down
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][17] = Button6;//R3 right thumb down

    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][15] = Button7;//back
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][20] = Button8;//Microsoft xbox button
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][14] = Button9;//start



    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][25].push_back(FSUSBElementInfoMap(0,255,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][26].push_back(FSUSBElementInfoMap(0,255,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][27].push_back(FSUSBElementInfoMap(-32768,32767,XAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][28].push_back(FSUSBElementInfoMap(-32768,32767,YAxis,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][29].push_back(FSUSBElementInfoMap(-32768,32767,XAxis2,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][30].push_back(FSUSBElementInfoMap(-32768,32767,YAxis2,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][18] = Button5;//L1 sholder button
    _usageMapToInputEvent[MicrosoftVentderID][MictrosftXbox360WindowsControllerID][19] = Button6;//R2 sholder button
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
        lookUpDeviceInputFromUSBID(vendorUSBID,
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
