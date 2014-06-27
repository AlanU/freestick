/**************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2013.

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

#include "FSHIDAndroidJoysickDeviceManager.h"
#include "../NULL/FSUSBNullDevice.h"
#include "./jni_wrapper.h"
#include <android/log.h>
#include "FSAndroidJoystick.h"
using namespace freestick;
FSHIDAndroidJoysickDeviceManager::FSHIDAndroidJoysickDeviceManager()
{
}



void FSHIDAndroidJoysickDeviceManager::init( )
{
    FSUSBDeviceManager::init();

    JNIBridge::registerDeviceWasAdded(this);
    JNIBridge::registerDeviceWasRemoved(this);
}



void FSHIDAndroidJoysickDeviceManager::gamepadWasAddedFromJINBridge(int deviceID)
{
    LOGI("From C++ GamePad was added ");
    _androidIDToIDMap[deviceID] = this->getNextID();
   this->addDevice(new FSAndroidJoystick(deviceID,this->getNextID(),0,0,0,false));
}

void FSHIDAndroidJoysickDeviceManager::gamepadWasRemovedFromJINBridge(int deviceID)\
{
     FSBaseDevice * device = NULL;
    if(_androidIDToIDMap.find(deviceID) != _androidIDToIDMap.end())
    {
        device = (FSBaseDevice *)this->getDevice(_androidIDToIDMap[deviceID]);
        _androidIDToIDMap.erase(deviceID);
    }
    if(device)
    {
        this->removeDevice(device);
    }
}


void FSHIDAndroidJoysickDeviceManager::addDevice(FSBaseDevice * device)
{
    FSUSBDeviceManager::addDevice(device);
}

void FSHIDAndroidJoysickDeviceManager::removeDevice(FSBaseDevice * device)
{
    FSUSBDeviceManager::removeDevice(device);
}


