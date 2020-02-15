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

FSUSBDevice::FSUSBDevice(idNumber id,
                         vendorIDType vendorID,
                         productIDType productID)
                         :FSBaseDevice(id)
{

    _vendorID = vendorID;
    _vendorIDFriendlyName = FSUSBDevice::GetFrendlyVendorNameFromID(vendorID);
    _productID = productID;
    _productIDFriendlyName = FSUSBDevice::GetFrendlyProductNameFromID(_vendorID,_productID);
    _friendlyName = _vendorIDFriendlyName + " "+ _productIDFriendlyName;

}

std::string FSUSBDevice::GetFrendlyProductNameFromID(vendorIDType vendorID, productIDType productID)
{
    static std::map<long, std::map<long,std::string > >s_productFriendlyNames;
    s_productFriendlyNames[LogitechVendorID][LogitechDualActionID] = "Dual Action";
    s_productFriendlyNames[SonyVendorID][Playstation3ControllerID] = "DualShock 3 Controller";
    s_productFriendlyNames[HVG2VendorID][HVG2TwinPS2] ="Twin DualShock 2";
    s_productFriendlyNames[SonyVendorID][Playstation4ControllerIDV1] = "DualShock 4 Controller";
    s_productFriendlyNames[SonyVendorID][Playstation4ControllerIDV2] = "DualShock 4 Controller (2nd Gen)";
    s_productFriendlyNames[GameElementsVendorID][GameElementsRecoilID] = "GGE908";
    s_productFriendlyNames[DragonRiseID][SteelSeries3GCControllerID] = "3GC Controller";


    if(s_productFriendlyNames.find(vendorID) != s_productFriendlyNames.end())
    {
        if(s_productFriendlyNames[vendorID].find(productID) != s_productFriendlyNames[vendorID].end())
        {
            return s_productFriendlyNames[vendorID][productID];
        }
    }
    return "unknown";//Call down and ask the device
}

 std::string  FSUSBDevice::GetFrendlyVendorNameFromID(vendorIDType vendorID)
{

     static std::map<long, std::string > s_vendorFriendlyNames;
    /** \todo
     *make this const
     */

     //
    s_vendorFriendlyNames[SonyVendorID] = "Sony";
    s_vendorFriendlyNames[MicrosoftVendorID] = "Microsoft";
    s_vendorFriendlyNames[LogitechVendorID] = "Logitech";
    s_vendorFriendlyNames[1149] = "Kensington";
    s_vendorFriendlyNames[1452] = "Fujitsu Takamisawa Component";
    s_vendorFriendlyNames[1635] = "Macsense";
    s_vendorFriendlyNames[8738] = "Macally";
    s_vendorFriendlyNames[1848] = "Mad Catz, Inc.";
    s_vendorFriendlyNames[SteelSeriesVendorID] = "SteelSeries";
    s_vendorFriendlyNames[DragonRiseID] =  s_vendorFriendlyNames[SteelSeriesVendorID];
    s_vendorFriendlyNames[AmazonVendorID] = "Amazon";
    s_vendorFriendlyNames[GameElementsVendorID] = "Game Elements";

    if(s_vendorFriendlyNames.find(vendorID) != s_vendorFriendlyNames.end())
        return s_vendorFriendlyNames[vendorID];
    else
        return "unknown"; //call down and ask the device


}
