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

#include "USB/platform/MacOSX/FSUSBMacOSXJoystick.h"
#include "../../../3rdParty/Mac/IOHID/IOHIDDevice_.h"
#include <IOKit/hid/IOHIDLib.h>
#include <IOKit/IOKitLib.h>
#include "USB/common/FSUSBJoystickDeviceManager.h"
#include <CoreFoundation/CoreFoundation.h>
#include "common/FreeStickLog.h"
#include "USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.h"
using namespace freestick;



unsigned int FSUSBMacOSXJoystick::Init(FSUSBJoystickDeviceManager & usbJoystickManager)
{
    CFArrayRef  deviceElements;
    unsigned int numberOfButtons = 0;
    unsigned int numberOfAnalogSticks = 0;
    unsigned int numberOfAnalogButtons = 0;
    IOHIDElementCookie elemnetID = 0;
    uint32_t usage = 0;
    uint32_t usagePage = 0;
    CFIndex uniqueElementID  = 0;
    //std::map<IOHIDElementCookie,int> idMap;
    CFIndex min = 0;
    CFIndex max  = 0;

    assert( IOHIDDeviceGetTypeID() == CFGetTypeID(_macIOHIDDeviceRef) );

    deviceElements = IOHIDDeviceCopyMatchingElements(_macIOHIDDeviceRef, NULL, kIOHIDOptionsTypeNone);
    CFIndex index;
    CFIndex deviceArrayCount = CFArrayGetCount(deviceElements);
    if(deviceArrayCount > 0)
    {
        for (index =0; index < deviceArrayCount;index++)
        {
            IOHIDElementRef elemnet = (IOHIDElementRef) CFArrayGetValueAtIndex(deviceElements, index);
            if(!elemnet)
                continue;

            if(IOHIDElementIsVirtual(elemnet))
                continue;

            IOHIDElementType type = IOHIDElementGetType(elemnet);
            min = IOHIDElementGetLogicalMin(elemnet);
            max = IOHIDElementGetLogicalMax(elemnet);
            elemnetID =IOHIDElementGetCookie(elemnet);
            usage =IOHIDElementGetUsage(elemnet);
            usagePage = IOHIDElementGetUsagePage(elemnet);
            uniqueElementID =  FSUSBMacOSXJoystickDeviceManager::createIdForElement(usage,usagePage,elemnetID,_vendorID,_productID);

            CFIndex value = 0;
            IOHIDValueRef   tIOHIDValueRef;
            //Checking the value of some elements of the ps3 controller cause blue tooth erros and IOHIDDeviceGetValue will never return
            if((_vendorID == SonyVendorID && _productID == Playstation3ControllerID))
            {
                value = min+max/2;
            }
            else
            {
                if ( kIOReturnSuccess == IOHIDDeviceGetValue(_macIOHIDDeviceRef, elemnet, &tIOHIDValueRef) )
                 {
                      if(CFGetTypeID(tIOHIDValueRef) == IOHIDValueGetTypeID())
                      {
                         if(IOHIDValueGetLength(tIOHIDValueRef) <= static_cast<CFIndex>(sizeof(CFIndex)))
                         {
                             value =  IOHIDValueGetIntegerValue(tIOHIDValueRef);

                         }
                      }
                 }
            }
            
            // FSUSBElementInfoMap  map = usbJoystickManager->lookUpDeviceInputFromUSBID(_vendorID,_productID,elementID,min,max,min);

            if(type == kIOHIDElementTypeInput_Axis || type == kIOHIDElementTypeInput_Button || type == kIOHIDElementTypeInput_Misc || type == kIOHIDElementTypeInput_ScanCodes)
            {
                if(min != max)
                {
                    EE_DEBUG<<"("<<min<<","<<max<<")"<<" ID: "<<elemnetID<<" unique id "<< uniqueElementID<<" Usage page" <<usagePage<< " Usage "<<usage<<" Value "<<value<<std::endl;
                }
                if (min == 0 && max == 1)
                {
                    numberOfButtons++;
                }
                else if ((min*-1) == (max+1) )
                {
                    numberOfAnalogSticks++;
                }
                else if (min == 0 && max > 1)
                {
                    numberOfAnalogButtons++;
                }
                FSUSBJoyStickInputElement temp(static_cast<unsigned int>(uniqueElementID), getJoystickID() ,static_cast<minMaxNumber>(min), static_cast<minMaxNumber>(max), _vendorID,_productID,usbJoystickManager,static_cast<physicalValueNumber> (value),elemnetID);
                this->addInputElement(temp);

            }

        }

    }
    CFRelease(deviceElements);
    

    /* if(TotalNumberOfButtons)
    {
        (*TotalNumberOfButtons) = numberOfButtons;
    }
    if(TotalNumberOfAxis)
    {
        (*TotalNumberOfAxis) =  numberOfAnalogSticks;
    }
    if(TotalNumberOfAnalogButtons)
    {
       (*TotalNumberOfAnalogButtons) = numberOfAnalogButtons;
    }
    return numberOfButtons + numberOfAnalogSticks + numberOfAnalogButtons;*/
    return 0;
}


FSUSBMacOSXJoystick::~FSUSBMacOSXJoystick()
{

    CFRelease(_macIOHIDDeviceRef);
}

FSUSBMacOSXJoystick::FSUSBMacOSXJoystick()
{
}

FSUSBMacOSXJoystick::FSUSBMacOSXJoystick(IOHIDDeviceRef device,
                                         idNumber joyStickID,
                                         unsigned int numberOfButtons,
                                         unsigned int numberOfAnlogSticks,
                                         unsigned int numberOfDigitalSticks,
                                         bool forceFeedBackSupported,
                                         const std::string & physicalDeviceUniqueID):FSUSBJoystick(joyStickID,
                                                                                     numberOfButtons,
                                                                                     numberOfAnlogSticks,
                                                                                     numberOfDigitalSticks,
                                                                                     forceFeedBackSupported,
                                                                                     0,
                                                                                     0 )
{
    _physicalDeviceUniqueID = physicalDeviceUniqueID;
    _vendorID = static_cast<vendorIDType>(IOHIDDevice_GetVendorID(device));
    _productID = static_cast<productIDType>( IOHIDDevice_GetProductID(device));

    EE_DEBUG<<"device with vendorID "<<_vendorID<<" and productID "<<_productID<<std::endl;
    _vendorIDFriendlyName = FSUSBDevice::getFrendlyVendorNameFromID(_vendorID);
    if(_vendorIDFriendlyName == "unknown")
    {
        CFStringRef manufactureStringRef = IOHIDDevice_GetManufacturer(device);
        if(manufactureStringRef)
        {
           std::string temp = CFStringRefToString(manufactureStringRef);
           if(!temp.empty())
           {
               _vendorIDFriendlyName = temp;
           }
        }
    }
    _productIDFriendlyName = FSUSBDevice::getFrendlyProductNameFromID(_vendorID,_productID);
    if(_productIDFriendlyName == "unknown")
    {
       CFStringRef productStringRef = IOHIDDevice_GetProduct(device);
       if(productStringRef)
       {
           std::string temp = CFStringRefToString(productStringRef);

           if(!temp.empty())
           {
               _productIDFriendlyName = temp;
           }
       }
    }
    _friendlyName = _vendorIDFriendlyName + " "+ _productIDFriendlyName;

    _macIOHIDDeviceRef = device;
    CFRetain(_macIOHIDDeviceRef);

}


std::string FSUSBMacOSXJoystick::CFStringRefToString(CFStringRef refString)
{

    const char * CStringstringPtr;
    if( ( CStringstringPtr = CFStringGetCStringPtr(refString,kCFStringEncodingUTF8) ) )
    {
        return std::string(CStringstringPtr);
    }
    else
    {
        CFIndex length = CFStringGetLength(refString);
        CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
        std::string strBuffer(maxSize, ' ');
        char * buffer = &*strBuffer.begin();
        if(CFStringGetCString(refString, buffer, maxSize, kCFStringEncodingUTF8))
        {
            return strBuffer;
        }
    }

    //bad convrsion
    if(!refString || CFStringGetLength(refString) == 0)
    {
        return std::string();
    }


    return std::string();


}

std::string FSUSBMacOSXJoystick::getManufactureName(IOHIDDeviceRef device)
{
    CFStringRef manufactureStringRef = IOHIDDevice_GetManufacturer(device);
    if(manufactureStringRef)
    {
       return CFStringRefToString(manufactureStringRef);

    }
    return std::string();
}

