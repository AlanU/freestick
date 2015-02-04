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

#include "USB/platform/Android/jni/src/FSHIDAndroidJoysickDeviceManager.h"
#include "USB/platform/NULL/FSUSBNullDevice.h"
#include "USB/platform/Android/jni/src/FSJNI_Wrapper.h"
#include <android/log.h>
#include <android/input.h>
#include <android/keycodes.h>
#include "USB/platform/Android/jni/src/FSAndroidJoystick.h"
using namespace freestick;
#define ANDROID_AXIS_X 0x00000000
#define ANDROID_AXIS_Y 0x00000001
#define ANDROID_AXIS_Z 0x0000000b
#define ANDROID_AXIS_RZ 0x0000000e
//standard for right trigger on android
#define ANDROID_AXIS_RTRIGGER 0x00000012
#define ANDROID_AXIS_THROTTLE 0x00000013
#define ANDROID_AXIS_GAS 0x00000016
//standard for left trigger on android
#define ANDROID_AXIS_LTRIGGER 0x00000011
#define ANDROID_AXIS_BRAKE 0x00000017

FSHIDAndroidJoysickDeviceManager::FSHIDAndroidJoysickDeviceManager()
{

    _androidUsageMapToInputEvent[AKEYCODE_DPAD_UP] = DPadUp;
    _androidUsageMapToInputEvent[AKEYCODE_DPAD_DOWN] = DPadDown;
    _androidUsageMapToInputEvent[AKEYCODE_DPAD_LEFT] = DPadLeft;
    _androidUsageMapToInputEvent[AKEYCODE_DPAD_RIGHT] = DPadRight;
    _androidUsageMapToInputEvent[AKEYCODE_DPAD_RIGHT] = DPadRight;
    _androidUsageMapToInputEvent[AKEYCODE_DPAD_CENTER] = ButtonA;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_X] = ButtonX;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_Y] = ButtonY;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_A] = ButtonA;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_B] = ButtonB;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_L1 ] = LeftShoulder;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_R1 ] = RightShoulder;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_L2 ] = LeftShoulder2;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_R2 ] = RightShoulder2;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_SELECT] = ButtonSelect;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_START] = ButtonStart;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_THUMBL] = Axis1Button;
    _androidUsageMapToInputEvent[AKEYCODE_BUTTON_THUMBR] = Axis2Button;

    _androidUsageMapToInputEvent[ANDROID_AXIS_X] = XAxis;
    _androidUsageMapToInputEvent[ANDROID_AXIS_Y] = YAxis;

    _androidUsageMapToInputEvent[ANDROID_AXIS_Z] = XAxis2;
    _androidUsageMapToInputEvent[ANDROID_AXIS_RZ] = YAxis2;

    _androidUsageMapToInputEvent[ANDROID_AXIS_RTRIGGER] = Trigger1;
    _androidUsageMapToInputEvent[ANDROID_AXIS_THROTTLE] = Trigger1;
    _androidUsageMapToInputEvent[ANDROID_AXIS_GAS] = Trigger1;

    _androidUsageMapToInputEvent[ANDROID_AXIS_LTRIGGER] = Trigger2;
    _androidUsageMapToInputEvent[ANDROID_AXIS_BRAKE] = Trigger2;




}


void FSHIDAndroidJoysickDeviceManager::init(JavaVM * jvm)
{
    _jvm = jvm;
    init();
    JNIBridge::updateJoysticks(_jvm);
}


void FSHIDAndroidJoysickDeviceManager::init( )
{
    FSUSBDeviceManager::init();

    JNIBridge::registerDeviceWasAdded(this);
    JNIBridge::registerDeviceWasRemoved(this);
    JNIBridge::registerDeviceWasUpdated(this);
}

void FSHIDAndroidJoysickDeviceManager::gamepadWasUpdatedFromJINBridge(int deviceid,int code,int type,float value,int min,int max)
{
    LOGI("From C++ GamePad was updated ");

    if(_androidIDToIDMap.find(deviceid) == _androidIDToIDMap.end())
    {
        LOGI("Could not find device %i",deviceid);
        return;
    }

    LOGI("device %i with code %i min %i max %i with value %f",deviceid,code,min,max,value);
    FSEventAction eventAction = FSInputRest;
    FSDeviceInput inputType = Unknown;
    bool isDigital = (max == 1 && min == 0) ? true : false;
    FreeStickEventType eventType;
    if(isDigital)
    {
        eventType = FS_BUTTON_EVENT;
        if(value == 0)   //down
        {  eventAction = FSInputPressed; }
    }
    else
    {
        eventType = FS_AXIS_EVENT;
    }

    if(_androidUsageMapToInputEvent.find(code) != _androidUsageMapToInputEvent.end())
    {
        inputType = _androidUsageMapToInputEvent[code];
    }

    if(inputType == Unknown)
    {
        LOGI("Unknow input type for %i ",code);
    }
    else if (inputType == Trigger1 || inputType == Trigger2)
    {
        eventType = FS_TRIGGER_EVENT;
    }

    else
    {
        LOGI("know input type for %i is %i",code,inputType);
        if(isDigital)
        {
            LOGI("inputOnDeviceChanged %f ",value);

            this->inputOnDeviceChanged(eventType,eventAction,inputType,_androidIDToIDMap[deviceid],code,value,0,min,max);
            LOGI("inputOnDeviceChanged returned %f ",value);

        }
        else
        {
            LOGI("inputOnDeviceChangedWithNormilzedValues %f ",value);

            this->inputOnDeviceChangedWithNormilzedValues(eventType,eventAction,inputType,_androidIDToIDMap[deviceid],code,value,0,min,max);

        }
    }



}


void FSHIDAndroidJoysickDeviceManager::gamepadWasAddedFromJINBridge(int deviceID,JavaVM * jvm)
{
    LOGI("From C++ GamePad was added ");
    if(_androidIDToIDMap.find(deviceID) == _androidIDToIDMap.end())
    {
        unsigned int newdeviceID = this->getNextID();
        _androidIDToIDMap[deviceID] = newdeviceID;
       this->addDevice(new FSAndroidJoystick(deviceID,newdeviceID,0,0,0,false,jvm));
    }
}

void FSHIDAndroidJoysickDeviceManager::gamepadWasRemovedFromJINBridge(int deviceID)\
{
      LOGI("From C++ GamePad trying to remove %i",deviceID);
     FSBaseDevice * device = NULL;
    if(_androidIDToIDMap.find(deviceID) != _androidIDToIDMap.end())
    {
        LOGI("From C++ GamePad was found and is going to be removed ");
        device = (FSBaseDevice *)this->getDevice(_androidIDToIDMap[deviceID]);
        if(device != NULL)
        {
            LOGI("From C++ GamePad is going to be removed ");
            this->removeDevice(device);
        }
        _androidIDToIDMap.erase(deviceID);
    }

}

void FSHIDAndroidJoysickDeviceManager::update()
{
    JNIBridge::updateJoysticks(_jvm);
}


