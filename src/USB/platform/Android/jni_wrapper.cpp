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

#include "jni_wrapper.h"
#include <android/input.h>
#include <jni.h>
std::vector<IJINICallBack*> JNIBridge::_deviceAddedCallback;
std::vector<IJINICallBack*> JNIBridge::_deviceRemovedCallback;
std::vector<IJINICallBack*> JNIBridge::_deviceUpdateCallback;
const int  InputDevice_SOURCE_GAMEPAD = 0x00000401;
const int  InputDevice_SOURCE_JOYSTICK = 0x01000010;
const int  InputDevice_SOURCE_DPAD = 0x00000201;

JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadDeviceUpdate(JNIEnv *env, jobject thisObj,jint deviceid,jint code,jint type,jfloat value,jint min,jint max)
{
    LOGI("JNI gamepadDeviceUpdate %i %i %f %i,%i",code,type,value,min,max);

    JNIBridge::updateValue(deviceid, code, type, value,min,max);
}

JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadWasAdded(JNIEnv *env, jobject thisObj,jint HID_ID)
{
    //  gamepadWasAdded(devicemanager,HID_ID);
    LOGI("JNI gamePadWasAdded");
    JNIBridge::update(HID_ID,0);
}

JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadWasRemoved(JNIEnv *env, jobject thisObj,jint HID_ID)
{
    //gamepadWasRemoved(devicemanager,HID_ID);
    LOGI("JNI gamePadWasRemoved");

    JNIBridge::update(HID_ID,1);

}


void JNIBridge::updateValue(int deviceid,int code,int type,float value,int min,int max)
{
    for(std::vector<IJINICallBack*>::iterator itr = _deviceUpdateCallback.begin();itr != _deviceUpdateCallback.end();itr++)
    {
        (*itr)->gamepadWasUpdatedFromJINBridge(deviceid, code, type, value,min,max);

    }
}

void JNIBridge::update(int hidDeviceID, int type)
{
    int t=hidDeviceID;
    switch(type)
    {
    case 0:
        for(std::vector<IJINICallBack*>::iterator itr = _deviceAddedCallback.begin();itr != _deviceAddedCallback.end();itr++)
        {
            LOGI("Call back from bridge");
            (*itr)->gamepadWasAddedFromJINBridge(hidDeviceID);
        }
        //run through the _devieAddedCallback map cand call the correct function
        break;
    case 1:
        for(std::vector<IJINICallBack*>::iterator itr = _deviceRemovedCallback.begin();itr != _deviceRemovedCallback.end();itr++)
        {
            LOGI("Call back from bridge for device remove");
            (*itr)->gamepadWasRemovedFromJINBridge(hidDeviceID);
        }
        break;

    }
}

void JNIBridge::registerDeviceWasAdded(IJINICallBack *listener)
{
    LOGI("Registed for device added");

    _deviceAddedCallback.push_back(listener);
}

void JNIBridge::registerDeviceWasRemoved(IJINICallBack *listener)
{
    LOGI("Registed for device remove");
    _deviceRemovedCallback.push_back(listener);
}

void JNIBridge::registerDeviceWasUpdated(IJINICallBack * listener)
{
    _deviceUpdateCallback.push_back(listener);
}

void  JNIBridge::updateJoysticks(JavaVM * jvm)
{
    JNIEnv *env;
    //TODO cache jclass and methodID
    jvm->AttachCurrentThread(&env,NULL);
    jclass inputDeviceClass = env->FindClass("android/view/InputDevice");

    if(!inputDeviceClass)
    {
        LOGI("call from updateJoysticks class not found");
        return ;
    }

    jmethodID getDeviceIDsMethodId = env->GetStaticMethodID(inputDeviceClass,"getDeviceIds","()[I");
    jobject deviceIdsObj = env->CallStaticObjectMethod(inputDeviceClass,getDeviceIDsMethodId);
    jintArray * deviceIdArray = (jintArray *)(&deviceIdsObj);
    int arrayLenght = env->GetArrayLength((*deviceIdArray));
    jint * devicesArray = env->GetIntArrayElements((*deviceIdArray),JNI_FALSE);

    LOGI("looking up device getDevice MethodID ");

    jmethodID getDeviceMethodId = env->GetStaticMethodID(inputDeviceClass,"getDevice","(I)Landroid/view/InputDevice;");
    if(!getDeviceMethodId)
    {
        LOGI("get device MethodID lookup failed");
        return;
    }
   // jmethodID toStringMethodID = env->GetMethodID(inputDeviceClass,"toString","()Ljava/lang/String;");


    LOGI("arraylenght %i",arrayLenght);
    for(int i = 0;i<arrayLenght;i++)
    {
        LOGI("Found Device in c++ %i index number %i",devicesArray[i],i);

        int currentID = devicesArray[i];
        //LOGI("Calling get Device: %p, %u, %u",env,getDeviceMethodId,currentID);

        jobject currentInputDevice=env->CallStaticObjectMethod(inputDeviceClass,getDeviceMethodId,currentID);

        if(currentInputDevice)
        {
            LOGI("found  Device");

            jclass deviceInstanceClass = env->GetObjectClass(currentInputDevice);
            if(!deviceInstanceClass)
            {
                LOGI("deviceInstanceClass not found");
                continue;
            }
            LOGI("calling getSources");
            jmethodID deviceSourcesMethodID = env->GetMethodID(deviceInstanceClass,"getSources","()I");

            if(!deviceSourcesMethodID)
            {
                LOGI("device sources MethodID lookup failed");
                return;
            }
            LOGI("Looking For Vaild Device");
            int sources = (int) env->CallIntMethod(currentInputDevice,deviceSourcesMethodID);
            if (((sources & InputDevice_SOURCE_GAMEPAD) == InputDevice_SOURCE_GAMEPAD)
                           || ((sources & InputDevice_SOURCE_JOYSTICK)
                           == InputDevice_SOURCE_JOYSTICK) || ((sources & InputDevice_SOURCE_DPAD)
                           == InputDevice_SOURCE_DPAD))
            {
                LOGI("Vaild Device in c++ %i index number %i",devicesArray[i],i);

            }
        }
        //TODO get device from id and check source
    }

}
