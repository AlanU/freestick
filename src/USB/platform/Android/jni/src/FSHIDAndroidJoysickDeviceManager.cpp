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
#include <stack>
#include "USB/platform/Android/jni/src/FSAndroidJoystick.h"
using namespace freestick;
#define ANDROID_AXIS_X 0
#define ANDROID_AXIS_Y 1
#define ANDROID_AXIS_Z 11
#define ANDROID_AXIS_RZ 14
//standard for right trigger on android
#define ANDROID_AXIS_RTRIGGER 18
#define ANDROID_AXIS_THROTTLE 19
#define ANDROID_AXIS_GAS 22
//standard for left trigger on android
#define ANDROID_AXIS_LTRIGGER 17
#define ANDROID_AXIS_BRAKE 23
//dpad when reporing as a hat stick
#define ANDROID_AXIS_HAT_X 15
#define ANDROID_AXIS_HAT_Y 16

void FSHIDAndroidJoysickDeviceManager::addAndroidMapping(unsigned int androidEventType,FSDeviceInput deviceInput)
{
    if(FS_isAxis(deviceInput) || FS_isTrigger(deviceInput))
    {
        _androidAxisnUsageMapToInputEvent[androidEventType] = deviceInput;
    }
    else
    {
        _androidButtonUsageMapToInputEvent[androidEventType] = deviceInput;
    }
}

FSHIDAndroidJoysickDeviceManager::FSHIDAndroidJoysickDeviceManager()
{

    _androidButtonUsageMapToInputEvent[AKEYCODE_DPAD_UP] = DPadUp;
    _androidButtonUsageMapToInputEvent[AKEYCODE_DPAD_DOWN] = DPadDown;
    _androidButtonUsageMapToInputEvent[AKEYCODE_DPAD_LEFT] = DPadLeft;
    _androidButtonUsageMapToInputEvent[AKEYCODE_DPAD_RIGHT] = DPadRight;
    _androidButtonUsageMapToInputEvent[AKEYCODE_DPAD_RIGHT] = DPadRight;
    _androidButtonUsageMapToInputEvent[AKEYCODE_DPAD_CENTER] = ButtonA;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_X] = ButtonX;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_Y] = ButtonY;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_A] = ButtonA;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_B] = ButtonB;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_L1] = LeftShoulder;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_R1] = RightShoulder;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_L2] = LeftShoulder2;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_R2] = RightShoulder2;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_SELECT] = ButtonSelect;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_START] = ButtonStart;
    _androidButtonUsageMapToInputEvent[AKEYCODE_MENU] = ButtonStart;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_THUMBL] = Axis1Button;
    _androidButtonUsageMapToInputEvent[AKEYCODE_BUTTON_THUMBR] = Axis2Button;

    _androidAxisnUsageMapToInputEvent[ANDROID_AXIS_X] = XAxis;
    _androidAxisnUsageMapToInputEvent[ANDROID_AXIS_Y] = YAxis;

    _androidAxisnUsageMapToInputEvent[ANDROID_AXIS_Z] = XAxis2;
    _androidAxisnUsageMapToInputEvent[ANDROID_AXIS_RZ] = YAxis2;

    _androidAxisnUsageMapToInputEvent[ANDROID_AXIS_LTRIGGER] = Trigger1;
    _androidAxisnUsageMapToInputEvent[ANDROID_AXIS_BRAKE] = Trigger1;

    _androidAxisnUsageMapToInputEvent[ANDROID_AXIS_RTRIGGER] = Trigger2;
    _androidAxisnUsageMapToInputEvent[ANDROID_AXIS_THROTTLE] = Trigger2;
    _androidAxisnUsageMapToInputEvent[ANDROID_AXIS_GAS] = Trigger2;


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

bool FSHIDAndroidJoysickDeviceManager::gamepadWasUpdatedFromJINBridge(int deviceid,int code,JNICallBackType type,float value,int min,int max)
{
    static std::stack<FSDeviceInput> lastDpadDownX;
    static std::stack<FSDeviceInput> lastDpadDownY;
    std::map<unsigned int,FSDeviceInput > * _androidUsageMapToInputEvent;
    LOGI("From C++ GamePad was updated with type %u",type);

    if(_androidIDToIDMap.find(deviceid) == _androidIDToIDMap.end())
    {
        LOGI("Could not find device %i",deviceid);
        return false;
    }

    if(type == MotionEvent)
    {
        _androidUsageMapToInputEvent = & _androidAxisnUsageMapToInputEvent;
    }
    else
    {
        _androidUsageMapToInputEvent = & _androidButtonUsageMapToInputEvent;
    }

    LOGI("device %i with code %i min %i max %i with value %f",deviceid,code,min,max,value);
    FSEventAction eventAction = FSInputRest;
    FSDeviceInput inputType = Unknown;
    bool isDigital = (max == 1 && min == 0) ? true : false;
    FreeStickEventType eventType;


    if(isDigital)
    {
        eventType = FS_BUTTON_EVENT;
        if(value == 0)   //down in android
        {  eventAction = FSInputPressed; }
    }
    else
    {
        eventType = FS_AXIS_EVENT;
    }


    if(_androidUsageMapToInputEvent->find(code) != _androidUsageMapToInputEvent->end())
    {
        inputType = (*_androidUsageMapToInputEvent)[code];
    }

    if (inputType == Trigger1 || inputType == Trigger2)
    {
        eventType = FS_TRIGGER_EVENT;

        //float newNormilzedValue = (value/(float)min);
        value = (value) * 2.0f-1.0f;
    }
    if(code == ANDROID_AXIS_HAT_X || code == ANDROID_AXIS_HAT_Y)
    {
         std::stack<FSDeviceInput> * lastDpadDown = &lastDpadDownY;
        if(code ==ANDROID_AXIS_HAT_X)
            lastDpadDown = &lastDpadDownX;

        eventType = FS_BUTTON_EVENT;

        eventAction = FSInputPressed;
        isDigital = true;
        if(value == 0)
        {
            while(!lastDpadDown->empty())
            {
                FSDeviceInput lastInput = lastDpadDown->top();
                lastDpadDown->pop();
                inputOnDeviceChanged(FS_BUTTON_EVENT,FSInputRest,lastInput,_androidIDToIDMap[deviceid],code,value,0,min,max);
            }
            LOGI("returning from last button press");

            return true;
        }
        else
        {
            switch(code)
            {
            case ANDROID_AXIS_HAT_X:
                inputType =  value>0 ? DPadRight : DPadLeft;
                lastDpadDownX.push(inputType);
                break;
            case ANDROID_AXIS_HAT_Y:
                inputType =  value>0 ? DPadDown : DPadUp;
                lastDpadDownY.push(inputType);
                break;
            }

            value = 1;
    }

    }
    if(inputType == Unknown)
    {
        LOGI("Unknown input type for %i ",code);
        return false;
    }
    else
    {
        LOGI("know input type for %i is %i",code,inputType);
        if(isDigital)
        {
            LOGI("inputOnDeviceChanged %f ",value);

            inputOnDeviceChanged(eventType,eventAction,inputType,_androidIDToIDMap[deviceid],code,value,0,min,max);
            LOGI("inputOnDeviceChanged returned %f ",value);

        }
        else
        {
            LOGI("inputOnDeviceChangedWithNormilzedValues %f ",value);

            inputOnDeviceChangedWithNormilzedValues(eventType,eventAction,inputType,_androidIDToIDMap[deviceid],code,value,0,min,max);

        }
        return true;
    }

}


void FSHIDAndroidJoysickDeviceManager::gamepadWasAddedFromJINBridge(int deviceID,JavaVM * jvm)
{
    LOGI("From C++ GamePad was added ");
    if(_androidIDToIDMap.find(deviceID) == _androidIDToIDMap.end())
    {
        ElementID newdeviceID = this->getNextID();
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


