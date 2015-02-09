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

#include "USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.h"
#include "USB/common/FSUSBJoystickDeviceManager.h"
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/hid/IOHIDLib.h>
#include <IOKit/IOKitLib.h>
#include <ForceFeedback/ForceFeedback.h>
#include "USB/platform/MacOSX/FSUSBMacOSXJoystick.h"
#include "stdio.h"
#include "../../../3rdParty/Mac/IOHID/IOHIDDevice_.h"
#include "common/FreeStickLog.h"

using namespace freestick;

FSUSBMacOSXJoystickDeviceManager::FSUSBMacOSXJoystickDeviceManager()
{
    IOHIDDeviceToIDMap.clear();
}

unsigned int FSUSBMacOSXJoystickDeviceManager::getDeviceIDFromIOHIDevice(IOHIDDeviceRef deviceRef)
{
    /** \todo
     * check to see if deive ref exist and return error if not
     */
    return IOHIDDeviceToIDMap[deviceRef];
}



void FSUSBMacOSXJoystickDeviceManager::addDevice(FSBaseDevice * device)
{
    if(device->getClassType() == FSUSBMACOSXJoystickType)
    {
        FSUSBMacOSXJoystick * macDevice = (FSUSBMacOSXJoystick *) device;
        IOHIDDeviceToIDMap[macDevice->GetIOHIDDeviceRef()] = device->getJoystickID();
    }
    FSUSBJoystickDeviceManager::addDevice(device);
}


void  FSUSBMacOSXJoystickDeviceManager::removeDevice(FSBaseDevice * device)
{

    if(device->getClassType() == FSUSBMACOSXJoystickType)
    {
        FSUSBMacOSXJoystick * macDevice = (FSUSBMacOSXJoystick *) device;
        IOHIDDeviceToIDMap.erase(macDevice->GetIOHIDDeviceRef());
    }
    FSUSBJoystickDeviceManager::removeDevice(device);
}



io_service_t AllocForceFeedBackDeviceFromIOHIDDevice(IOHIDDeviceRef device)
{
    io_service_t FFDevice = 0L;
    if(device)
    {
        CFMutableDictionaryRef matchDict = IOServiceMatching(kIOHIDDeviceKey);
        if(matchDict)
        {
            CFTypeRef typeRef = IOHIDDeviceGetProperty( device, CFSTR(kIOHIDLocationIDKey) );
            if(typeRef)
            {
                CFDictionaryAddValue(matchDict, CFSTR(kIOHIDLocationIDKey), typeRef);
                FFDevice =  IOServiceGetMatchingService(kIOMasterPortDefault, matchDict);

            }
        }
    }
    return FFDevice;
}

bool FreeFFDevice(io_service_t FFDevice)
{
    kern_return_t results;
    results = IOObjectRelease(FFDevice);
    return (kIOReturnSuccess == results);
}

bool isForceFeedBackSupported(IOHIDDeviceRef device)
{
    io_service_t FFDevice;
    FFCAPABILITIES FFDeviceAblities;
    FFDeviceObjectReference FFDeviceRef;
    bool returnValue = false;
    FFDevice = AllocForceFeedBackDeviceFromIOHIDDevice(device);
    if(FFIsForceFeedback(FFDevice)== FF_OK)
    {
        if(FFCreateDevice(FFDevice, &FFDeviceRef) == FF_OK)
        {
            if(FFDeviceGetForceFeedbackCapabilities(FFDeviceRef,&FFDeviceAblities) == FF_OK)
            {
                returnValue = true;
            }

        }
    }
    FreeFFDevice(FFDevice);
    return returnValue;
}

void vibrateJoystick(IOHIDDeviceRef device)
{
    io_service_t FFDevice;
    FFCAPABILITIES FFDeviceAblities;
    FFDeviceObjectReference FFDeviceRef;
    FFEFFECT 		pEffectDefinition;
    memset(&pEffectDefinition, 0, sizeof(FFEFFECT));
    pEffectDefinition.dwSize = sizeof(FFEFFECT);
    pEffectDefinition.dwSamplePeriod= 0;
    pEffectDefinition.dwGain = 10000;
    pEffectDefinition.dwFlags = FFEFF_OBJECTOFFSETS;
    FFENVELOPE EnVelop;
    memset(&EnVelop,0,sizeof(FFENVELOPE));
    pEffectDefinition.lpEnvelope=&EnVelop;
    EnVelop.dwSize= sizeof(FFENVELOPE);


    FFEffectObjectReference 	pEffectReference;

    HRESULT reslut;
    CFUUIDRef uuidRef = kFFEffectType_ConstantForce_ID;

    FFDevice = AllocForceFeedBackDeviceFromIOHIDDevice(device);
    if(FFIsForceFeedback(FFDevice)== FF_OK)
    {
        if(FFCreateDevice(FFDevice, &FFDeviceRef) == FF_OK)
        {
            FFDeviceGetForceFeedbackCapabilities(FFDeviceRef,&FFDeviceAblities);
            if( FFDeviceSendForceFeedbackCommand(FFDeviceRef, FFSFFC_RESET) ==FF_OK)
            {
                reslut = FFDeviceSendForceFeedbackCommand(FFDeviceRef, FFSFFC_SETACTUATORSON);
            }
            reslut =FFDeviceCreateEffect(FFDeviceRef,
                                         kFFEffectType_ConstantForce_ID,
                                         &pEffectDefinition,
                                         &pEffectReference
                                         );
            if(reslut == FF_OK)
            {
                // FFEffectDownload(pEffectReference);
                FFEffectStart(pEffectReference,1,FFES_SOLO);

            }
        }
    }
    FreeFFDevice(FFDevice);
}

unsigned int numberOfDeviecType(IOHIDDeviceRef device,int * TotalNumberOfButtons,int * TotalNumberOfAxis,int * TotalNumberOfAnalogButtons)
{
    CFArrayRef  deviceElements;
    unsigned int numberOfButtons = 0;
    unsigned int numberOfAnalogSticks = 0;
    unsigned int numberOfAnalogButtons = 0;
    IOHIDElementCookie elemnetID = 0;
    uint32_t usage = 0;
    uint32_t usagePage = 0;
    //std::map<IOHIDElementCookie,int> idMap;
    CFIndex min = 0;
    CFIndex max  = 0;
    if (device) {
        assert( IOHIDDeviceGetTypeID() == CFGetTypeID(device) );

        deviceElements = IOHIDDeviceCopyMatchingElements(device, NULL, kIOHIDOptionsTypeNone);
        CFIndex index;
        CFIndex deviceArrayCount = CFArrayGetCount(deviceElements);
        if(deviceArrayCount > 0)
        {
            for (index =0; index < deviceArrayCount;index++)
            {
                IOHIDElementRef elemnet = (IOHIDElementRef) CFArrayGetValueAtIndex(deviceElements, index);
                if(!elemnet)
                    continue;

                IOHIDElementType type = IOHIDElementGetType(elemnet);
                min = IOHIDElementGetLogicalMin(elemnet);
                max = IOHIDElementGetLogicalMax(elemnet);
                elemnetID =IOHIDElementGetCookie(elemnet);
                usage =IOHIDElementGetUsage(elemnet);
                usagePage = IOHIDElementGetUsagePage(elemnet);
                CFStringRef name = IOHIDElementGetName(elemnet);
                const char * nameChar = CFStringGetCStringPtr(name,kCFStringEncodingASCII);
                CFIndex value = 0;
                IOHIDValueRef   tIOHIDValueRef;
                /*  if ( kIOReturnSuccess == IOHIDDeviceGetValue(device, elemnet, &tIOHIDValueRef) )
                 {
                      if(CFGetTypeID(tIOHIDValueRef) == IOHIDValueGetTypeID())
                      {
                         if(IOHIDValueGetLength(tIOHIDValueRef) <= sizeof(CFIndex))
                         {
                             value =  IOHIDValueGetIntegerValue(tIOHIDValueRef);

                         }
                      }
                 }*/
                if(type == kIOHIDElementTypeInput_Axis || type == kIOHIDElementTypeInput_Button )// type == kIOHIDElementTypeInput_Misc || type == kIOHIDElementTypeInput_ScanCodes)
                {
                    if(value != 0)
                    {
                        int t=0;

                    }
                    if(min != max)
                    {

                        EE_DEBUG<<"("<<min<<","<<max<<")"<<" ID: "<<elemnetID<<" name "<<(nameChar?nameChar:"")<<" Usage page" <<usagePage<< " Usage "<<usage<<" Value "<<value<<std::endl;
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

                }

            }

        }
    }
    if(TotalNumberOfButtons)
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
    return numberOfButtons + numberOfAnalogSticks + numberOfAnalogButtons;
}


unsigned int numberOfButtons(IOHIDDeviceRef device)
{

    int numberbuttons = 0 ;
    int numberOfAnalogButtons = 0;
    numberOfDeviecType(device,& numberbuttons,NULL,& numberOfAnalogButtons);

    return numberbuttons + numberOfAnalogButtons;
}

unsigned int numberOfAnalogSticks(IOHIDDeviceRef device)
{
    int numberOfAnalogSticks = 0;
    numberOfDeviecType(device,NULL,& numberOfAnalogSticks,NULL);
    return numberOfAnalogSticks/2;
}

unsigned int numberOfAnalogAxis(IOHIDDeviceRef device)
{
    int numberOfAnalogSticks = 0;
    numberOfDeviecType(device,NULL,& numberOfAnalogSticks,NULL);
    return numberOfAnalogSticks;
}

void FSUSBMacOSXJoystickDeviceManager::findDpad(IOHIDDeviceRef device)
{
    return ;
    CFStringRef keys[2];
    CFNumberRef values[2];
    CFDictionaryRef criterion;
    int  GD = kHIDPage_GenericDesktop;
    int usage = kHIDUsage_GD_Hatswitch;
    values[0]= CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &GD);
    values[1]= CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &usage);
    keys[0] = CFSTR(kIOHIDElementUsagePageKey);
    keys[1] = CFSTR(kIOHIDElementUsageKey);
    signed long deviceArrayCount  = 0;
    criterion = CFDictionaryCreate(NULL, (const void **)keys, (const void **)values, 2, &kCFCopyStringDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    if (device) {
        assert( IOHIDDeviceGetTypeID() == CFGetTypeID(device) );

        CFArrayRef  deviceElements = IOHIDDeviceCopyMatchingElements(device, criterion, kIOHIDOptionsTypeSeizeDevice);
        CFIndex index;
        if(!deviceElements)
            return;
        deviceArrayCount = CFArrayGetCount(deviceElements);
        if(deviceArrayCount > 0)
        {
            for (index =0; index < deviceArrayCount;index++)
            {
                IOHIDElementRef elemnet = (IOHIDElementRef) CFArrayGetValueAtIndex(deviceElements, index);
                if(!elemnet)
                    continue;
                this->addMapping(getDeviceIDFromIOHIDevice(device),IOHIDElementGetCookie(elemnet),DPadUp);
            }
        }
    }

}

void FSUSBMacOSXJoystickDeviceManager::gamepadWasAdded(void* inContext, IOReturn inResult, void* inSender, IOHIDDeviceRef device) {
    FSUSBMacOSXJoystickDeviceManager * manager = (FSUSBMacOSXJoystickDeviceManager *) inContext;
    manager->addDevice(device);

    // vibrateJoystick(device);
}

void FSUSBMacOSXJoystickDeviceManager::gamepadWasRemoved(void* inContext, IOReturn inResult, void* inSender, IOHIDDeviceRef device) {
    FSUSBMacOSXJoystickDeviceManager * manager = (FSUSBMacOSXJoystickDeviceManager *) inContext;
    manager->removeDevice(device);
    EE_DEBUG<<"Gamepad was unplugged"<<std::endl;
}

void FSUSBMacOSXJoystickDeviceManager::gamepadAction(void* inContext, IOReturn inResult, void* inSender, IOHIDValueRef value) {
    IOHIDElementRef element = IOHIDValueGetElement(value);
    IOHIDElementType type = IOHIDElementGetType(element);
    if(!(type == kIOHIDElementTypeInput_Axis || type == kIOHIDElementTypeInput_Button || type == kIOHIDElementTypeInput_Misc || type == kIOHIDElementTypeInput_ScanCodes))
    {
        return ;
    }

    IOHIDDeviceRef device = IOHIDElementGetDevice(element);
    uint32_t usage = 0;
    uint32_t usagePage = 0;
    uint32_t elementID = IOHIDElementGetCookie(element);
    CFIndex min = IOHIDElementGetLogicalMin(element);
    CFIndex max = IOHIDElementGetLogicalMax(element);


    //if(min+1 != max)
    //  return;

    int elementValue = 0;
    if(IOHIDValueGetLength(value) > sizeof(CFIndex))
    {
        //  printf("\n");
        return ;
    }

    EE_DEBUG<<"Gamepad talked! type of input "<<(unsigned int)IOHIDElementGetType(element)<<" id: "<< elementID<<std::endl;

    elementValue=  IOHIDValueGetIntegerValue(value);
    double_t elementScaleValue = IOHIDValueGetScaledValue(value,kIOHIDValueScaleTypeCalibrated);
    usage =IOHIDElementGetUsage(element);
    usagePage = IOHIDElementGetUsagePage(element);
    if(type == kIOHIDElementTypeInput_Button || type == kIOHIDElementTypeInput_Misc )
    {

        //CFShow(element);
        //printf("Element: %s \n", element);

        EE_DEBUG<<"Element value: "<<elementValue<<" element scaled value "<<elementScaleValue<<std::endl;

        EE_DEBUG<<"Element Usage page"<<usagePage<<" with Usage "<<usage<<" min "<<min<<" max "<<max<<std::endl;
    }
    FSUSBMacOSXJoystickDeviceManager * manager = (FSUSBMacOSXJoystickDeviceManager *) inContext;
    unsigned int deviceID = manager->getDeviceIDFromIOHIDevice(device);
    const FSUSBJoystick * fsDevice = manager->getUSBJoystickDevice(deviceID);
    FSUSBJoyStickInputElement * elementDevice = NULL;
    if(fsDevice)
    {
        elementDevice =  (FSUSBJoyStickInputElement * )fsDevice->findInputElement(elementID);
    }
    if(elementDevice)
    {
        //  FSUSBElementInfoMap inputType = manager->lookUpDeviceInputFromID(deviceID,(unsigned int)IOHIDElementGetCookie(element),IOHIDElementGetLogicalMin(element),IOHIDElementGetLogicalMax(element),elementValue);
        // FreeStickEventType eventType =  IFSEvent::getEventFromInputType(inputType.getDeviceInput());
        FSUSBElementInfoMap inputType = elementDevice->getMapping(elementValue);
       bool isValueVaild = elementDevice->isValueInDeadZone(elementValue);
        FreeStickEventType eventType =  IFSEvent::getEventFromInputType(inputType.getDeviceInput());

        //pass in FSEventMaping so we can map release vs press
        if( eventType != FS_LAST_EVENT && inputType.getDeviceInput() != LastInput)
        {

            if(!isValueVaild)
            {
                manager->inputOnDeviceChangedWithNormilzedValues(eventType,inputType.getEventMapping(),inputType.getDeviceInput(),
                                                                 deviceID,elementDevice->getJoystickID(),
                                                                 0,0,
                                                                -1,
                                                                 1);
            }
            else
            {
                manager->inputOnDeviceChanged(eventType,inputType.getEventMapping(),inputType.getDeviceInput(),
                                              deviceID,elementDevice->getJoystickID(),
                                              elementDevice->getValue(),0,
                                              IOHIDElementGetLogicalMin(element),
                                              IOHIDElementGetLogicalMax(element));
            }
     

        }
    }
    EE_DEBUG<<std::endl;
}


void setupIOHDIManager(IOHIDManagerRef & hidManager,int device,void * thisptr )
{
    hidManager = IOHIDManagerCreate( kCFAllocatorDefault, kIOHIDOptionsTypeNone);
    CFStringRef keys[2];
    CFNumberRef values[2];
    CFDictionaryRef criterion;
    int  GD = kHIDPage_GenericDesktop;
    values[0]= CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &GD);
    values[1]= CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &device);
    keys[0] = CFSTR(kIOHIDDeviceUsagePageKey);
    keys[1] = CFSTR(kIOHIDDeviceUsageKey);
    criterion = CFDictionaryCreate(NULL, (const void **)keys, (const void **)values, 2, &kCFCopyStringDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    IOHIDManagerSetDeviceMatching(hidManager, criterion);
    IOHIDManagerRegisterDeviceMatchingCallback(hidManager, FSUSBMacOSXJoystickDeviceManager::gamepadWasAdded,thisptr);
    IOHIDManagerRegisterDeviceRemovalCallback(hidManager, FSUSBMacOSXJoystickDeviceManager::gamepadWasRemoved,thisptr);
    IOHIDManagerScheduleWithRunLoop(hidManager, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);

    //IOReturn tIOReturn =
    IOHIDManagerOpen(hidManager, kIOHIDOptionsTypeSeizeDevice);
    IOHIDManagerRegisterInputValueCallback(hidManager,  FSUSBMacOSXJoystickDeviceManager::gamepadAction, thisptr);
    //IOHIDManagerRegisterInputReportCallback( hidManager,foo,thisptr);
    CFRelease(criterion);
    CFRelease(values[0]);
    CFRelease(values[1]);

}


void FSUSBMacOSXJoystickDeviceManager::init()
{
    FSUSBJoystickDeviceManager::init();
    setupIOHDIManager(hidManagerGamePad, kHIDUsage_GD_GamePad,this);
    setupIOHDIManager(hidManagerJoyStick, kHIDUsage_GD_Joystick,this);


}

void FSUSBMacOSXJoystickDeviceManager::update()
{
    if(IOHIDDeviceToIDMap.begin() != IOHIDDeviceToIDMap.end())
    {
        std::map<IOHIDDeviceRef,unsigned int>::iterator itr = IOHIDDeviceToIDMap.begin();
        /*for(itr ; itr != IOHIDDeviceToIDMap.end() ; itr++ )
         {
           //numberOfDeviecType(itr->first,NULL,NULL,NULL);
         }*/
    }
}

FSUSBMacOSXJoystickDeviceManager::~FSUSBMacOSXJoystickDeviceManager()
{
    
    IOHIDManagerUnscheduleFromRunLoop(hidManagerGamePad, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
    IOHIDManagerUnscheduleFromRunLoop(hidManagerJoyStick, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);

    IOReturn  retunValue = IOHIDManagerClose(hidManagerGamePad,0);
    CFRelease(hidManagerGamePad);

    retunValue = IOHIDManagerClose(hidManagerJoyStick,0);
    CFRelease(hidManagerJoyStick);
}

void FSUSBMacOSXJoystickDeviceManager::addDevice(IOHIDDeviceRef  device)
{
    FSUSBMacOSXJoystick * temp = new FSUSBMacOSXJoystick(device, this->getNextID(),numberOfButtons(device),numberOfAnalogSticks(device),0,isForceFeedBackSupported(device));
    temp->Init(*this);
    this->addDevice(temp);
    findDpad(device);
    EE_DEBUG<<"Gamepad was plugged in with "<<temp->getNumberOfButtons()<<" buttons and "<<temp->getNumberOfAnlogSticks()<<" sticks"<<std::endl;

}

void FSUSBMacOSXJoystickDeviceManager::removeDevice(IOHIDDeviceRef device)
{
    if(this->IOHIDDeviceToIDMap.find(device) != IOHIDDeviceToIDMap.end())
    {
        this->removeDevice((FSBaseDevice *)this->getDevice(this->IOHIDDeviceToIDMap[device]));
    }
}
