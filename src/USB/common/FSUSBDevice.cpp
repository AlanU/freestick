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
    _vendorIDFriendlyName = FSUSBDevice::getFrendlyVendorNameFromID(vendorID);
    _productID = productID;
    _productIDFriendlyName = FSUSBDevice::getFrendlyProductNameFromID(_vendorID,_productID);
    _friendlyName = _vendorIDFriendlyName + " "+ _productIDFriendlyName;

}

std::string FSUSBDevice::getFrendlyProductNameFromID(vendorIDType vendorID, productIDType productID)
{
    static std::map<long, std::map<long,std::string > >s_productFriendlyNames;
    s_productFriendlyNames[kLogitechVendorID][kLogitechDualActionID] = "Dual Action";
    s_productFriendlyNames[kSonyVendorID][kPlaystation3ControllerID] = "DualShock 3 Controller";
    s_productFriendlyNames[kHVG2VendorID][kHVG2TwinPS2] ="Twin DualShock 2";
    s_productFriendlyNames[kSonyVendorID][kPlaystation4ControllerIDV1] = "DualShock 4 Controller";
    s_productFriendlyNames[kSonyVendorID][kPlaystation4ControllerIDV2] = "DualShock 4 Controller (2nd Gen)";
    s_productFriendlyNames[kGameElementsVendorID][kGameElementsRecoilID] = "GGE908";
    s_productFriendlyNames[kDragonRiseID][kSteelSeries3GCControllerID] = "3GC Controller";


    if(s_productFriendlyNames.find(vendorID) != s_productFriendlyNames.end())
    {
        if(s_productFriendlyNames[vendorID].find(productID) != s_productFriendlyNames[vendorID].end())
        {
            return s_productFriendlyNames[vendorID][productID];
        }
    }
    return "unknown";//Call down and ask the device
}

std::string FSUSBDevice::getFrendlyVendorNameFromID(vendorIDType vendorID){
     static std::map<long, std::string > s_vendorFriendlyNames;
    /** \todo *make this const */
    s_vendorFriendlyNames[kSonyVendorID] = "Sony";
    s_vendorFriendlyNames[kMicrosoftVendorID] = "Microsoft";
    s_vendorFriendlyNames[kLogitechVendorID] = "Logitech";
    s_vendorFriendlyNames[1149] = "Kensington";
    s_vendorFriendlyNames[1452] = "Fujitsu Takamisawa Component";
    s_vendorFriendlyNames[1635] = "Macsense";
    s_vendorFriendlyNames[8738] = "Macally";
    s_vendorFriendlyNames[1848] = "Mad Catz, Inc.";
    s_vendorFriendlyNames[kSteelSeriesVendorID] = "SteelSeries";
    s_vendorFriendlyNames[kDragonRiseID] =  s_vendorFriendlyNames[kSteelSeriesVendorID];
    s_vendorFriendlyNames[kAmazonVendorID] = "Amazon";
    s_vendorFriendlyNames[kGameElementsVendorID] = "Game Elements";
    if(s_vendorFriendlyNames.find(vendorID) != s_vendorFriendlyNames.end())
        return s_vendorFriendlyNames[vendorID];
      return "unknown"; //call down and ask the device
}
