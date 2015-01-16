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

#pragma once
#include "../../baseClasses/FSBaseDevice.h"
#include <string>
#include <map>
namespace freestick
{

    class FSUSBDevice : public FSBaseDevice
    {
    private:

    protected:
         FSUSBDevice();
         long _vendorID;
         std::string _vendorIDFriendlyName;
         long _productID;
         std::string _prodcutIDFriendlyName;
    public:
       FSUSBDevice(unsigned int id,
                   long venderID,
                   long productID);
       virtual FSDeviceType getClassType() const {return FSUSBDeviceType;}
       const std::string getVenderFriendlyName() const { return _vendorIDFriendlyName;}
       const std::string getProductFrendlyName() const { return _prodcutIDFriendlyName;}
       long getProductID() const{ return _productID;}
       long getVenderID() const { return _vendorID;}
       static std::string GetFrendlyVenderNameFromID(long venderID);
       static std::string GetFrendlyProductNameFromID(long venderID, long productID);

    };
}
