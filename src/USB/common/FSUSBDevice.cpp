/**************************************************************************
Created by Alan Uthoff on 10/13/2013
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

#include "USB/common/FSUSBDevice.h"
#include "USB/common/FSUSBDeviceManager.h"
using namespace freestick;
FSUSBDevice::FSUSBDevice()
{
}

FSUSBDevice::FSUSBDevice(IDNumber id,
                         long venderID,
                         long productID)
                         :FSBaseDevice(id)
{

    _vendorID = venderID;
    _vendorIDFriendlyName = FSUSBDevice::GetFrendlyVenderNameFromID(venderID);
    _productID = productID;
    _prodcutIDFriendlyName = FSUSBDevice::GetFrendlyProductNameFromID(_vendorID,_productID);
    _friendlyName = _vendorIDFriendlyName + " "+ _prodcutIDFriendlyName;

}

std::string FSUSBDevice::GetFrendlyProductNameFromID(long venderID, long productID)
{
    static std::map<long, std::map<long,std::string > >s_productFriendlyNames;
    s_productFriendlyNames[LogitechVendorID][LogitechDualActionID] = "Dual Action";
    s_productFriendlyNames[SonyVendorID][Playstation3ControllerID] = "DualShock 3 Controller";
    s_productFriendlyNames[HVG2VenderID][HVG2TwinPS2] ="Twin DualShock 2";
    s_productFriendlyNames[SonyVendorID][Playstation4ControllerID] = "DualShock 4 Controller";
    s_productFriendlyNames[GameElementsVendorID][GameElementsRecoilID] = "GGE908";
    s_productFriendlyNames[DragonRiseID][SteelSeries3GCControllerID] = "3GC Controller";


    if(s_productFriendlyNames.find(venderID) != s_productFriendlyNames.end())
    {
        if(s_productFriendlyNames[venderID].find(productID) != s_productFriendlyNames[venderID].end())
        {
            return s_productFriendlyNames[venderID][productID];
        }
    }
    return "unknown";//Call down and ask the device
}

 std::string  FSUSBDevice::GetFrendlyVenderNameFromID(long venderID)
{

     static std::map<long, std::string > s_venderFriendlyNames;
    /** \todo
     *make this const
     */

     //
    s_venderFriendlyNames[SonyVendorID] = "Sony";
    s_venderFriendlyNames[MicrosoftVendorID] = "Microsoft";
    s_venderFriendlyNames[LogitechVendorID] = "Logitech";
    s_venderFriendlyNames[1149] = "Kensington";
    s_venderFriendlyNames[1452] = "Fujitsu Takamisawa Component";
    s_venderFriendlyNames[1635] = "Macsense";
    s_venderFriendlyNames[8738] = "Macally";
    s_venderFriendlyNames[1848] = "Mad Catz, Inc.";
    s_venderFriendlyNames[SteelSeriesVendorID] = "SteelSeries";
    s_venderFriendlyNames[DragonRiseID] =  s_venderFriendlyNames[SteelSeriesVendorID];
    s_venderFriendlyNames[AmazonVendorID] = "Amazon";
    s_venderFriendlyNames[GameElementsVendorID] = "Game Elements";

    if(s_venderFriendlyNames.find(venderID) != s_venderFriendlyNames.end())
        return s_venderFriendlyNames[venderID];
    else
        return "unknown"; //call down and ask the device


}
