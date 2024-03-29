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

#include "USB/platform/Android/jni/src/FSJNI_Wrapper.h"
#include <android/input.h>
#include <algorithm>
#include <jni.h>
#include <string>
std::vector<IJNICallBack*> JNIBridge::_deviceAddedCallback;
std::vector<IJNICallBack*> JNIBridge::_deviceRemovedCallback;
std::vector<IJNICallBack*> JNIBridge::_deviceUpdateCallback;

const int  InputDevice_SOURCE_GAMEPAD = 0x00000401;
const int  InputDevice_SOURCE_JOYSTICK = 0x01000010;
const int  InputDevice_SOURCE_DPAD = 0x00000201;


JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_updateJoystickConnectedStatus(JNIEnv *env, jobject thisObj )
{
	 JavaVM * jvm;
	 env->GetJavaVM(&jvm);
	 JNIBridge::updateJoysticks(jvm);
}

JNIEXPORT bool JNICALL Java_org_freestick_FreestickDeviceManager_gamepadDeviceUpdate(JNIEnv *env, jobject thisObj,jint deviceid,jint code,jint type,jfloat value,jint min,jint max)
{
    FS_LOGI("JNI gamepadDeviceUpdate %i %i %f %i,%i",code,type,value,min,max);


    return JNIBridge::updateValue(deviceid, code,static_cast<JNICallBackType> (type), value,min,max);
}

JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadWasAdded(JNIEnv *env, jobject thisObj,jint HID_ID)
{
    //  gamepadWasAdded(devicemanager,HID_ID);
    FS_LOGI("JNI gamePadWasAdded");
    JavaVM * jvm;
    env->GetJavaVM(&jvm);
    JNIBridge::update(HID_ID,UpdateType::addedDevice,jvm);
}

JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadWasRemoved(JNIEnv *env, jobject thisObj,jint HID_ID)
{
    //gamepadWasRemoved(devicemanager,HID_ID);
    FS_LOGI("JNI gamePadWasRemoved");

    JNIBridge::update(HID_ID,UpdateType::removedDevice);

}


bool JNIBridge::updateValue(int deviceid,int code,JNICallBackType type,float value,int min,int max)
{
    bool returnValue = false;
    for(std::vector<IJNICallBack*>::iterator itr = _deviceUpdateCallback.begin();itr != _deviceUpdateCallback.end();++itr)
    {
        returnValue = returnValue || (*itr)->gamepadWasUpdatedFromJINBridge(deviceid, code, type, value,min,max);

    }
    return returnValue;
}
void JNIBridge::update(int hidDeviceID, UpdateType type)
{
	JNIBridge::update(hidDeviceID,type,NULL);
}

void JNIBridge::update(int hidDeviceID, UpdateType type, JavaVM * jvm)
{
    int t=hidDeviceID;
    switch(type)
    { 
    case UpdateType::addedDevice: //  addedDevice = 0
        for(std::vector<IJNICallBack*>::iterator itr = _deviceAddedCallback.begin();itr != _deviceAddedCallback.end();++itr)
        {
            FS_LOGI("Call back from bridge added device");
            (*itr)->gamepadWasAddedFromJINBridge(hidDeviceID,jvm);
        }
        //run through the _devieAddedCallback map cand call the correct function
        break;
    case UpdateType::removedDevice: // removedDevice = 1
        for(std::vector<IJNICallBack*>::iterator itr = _deviceRemovedCallback.begin();itr != _deviceRemovedCallback.end();++itr)
        {
            FS_LOGI("Call back from bridge for device remove");
            (*itr)->gamepadWasRemovedFromJINBridge(hidDeviceID);
        }
        break;

    }
}

void JNIBridge::registerDeviceWasAdded(IJNICallBack *listener)
{
    FS_LOGI("Registed for device added");

    _deviceAddedCallback.push_back(listener);
}

void JNIBridge::registerDeviceWasRemoved(IJNICallBack *listener)
{
    FS_LOGI("Registed for device remove");
    _deviceRemovedCallback.push_back(listener);
}

void JNIBridge::registerDeviceWasUpdated(IJNICallBack * listener)
{
    _deviceUpdateCallback.push_back(listener);
}

void  JNIBridge::updateJoysticks(JavaVM * jvm)
{
    std::vector<jint> currentAttachedJoysticks;
    std::vector<jint> foundJoysticks;
    JNIEnv *env;
    //TODO cache jclass and methodID
#ifdef JDK1_4
    jvm->AttachCurrentThread((void**)(&env),NULL);
#else
    //Old jdk pre 1.4
    jvm->AttachCurrentThread(&env,NULL);
#endif
    jclass inputDeviceClass = env->FindClass("android/view/InputDevice");

    if(!inputDeviceClass)
    {
        FS_LOGI("call from updateJoysticks class not found");
        return ;
    }

    jmethodID getDeviceIDsMethodId = env->GetStaticMethodID(inputDeviceClass,"getDeviceIds","()[I");
    jobject deviceIdsObj = env->CallStaticObjectMethod(inputDeviceClass,getDeviceIDsMethodId);
    jintArray * deviceIdArray = (jintArray *)(&deviceIdsObj);
    int arrayLength = env->GetArrayLength(*deviceIdArray);
    jint* devicesArray = env->GetIntArrayElements(*deviceIdArray, nullptr);


   // FS_LOGI("looking up device getDevice MethodID ");

    jmethodID getDeviceMethodId = env->GetStaticMethodID(inputDeviceClass,"getDevice","(I)Landroid/view/InputDevice;");
    if(!getDeviceMethodId)
    {
        FS_LOGI("get device MethodID lookup failed");
        return;
    }
   // jmethodID toStringMethodID = env->GetMethodID(inputDeviceClass,"toString","()Ljava/lang/String;");


    FS_LOGI("arraylenght %i",arrayLength);
    for(int i = 0;i<arrayLength;i++)
    {
        //FS_LOGI("Found Device in c++ %i index number %i",devicesArray[i],i);

        int currentID = devicesArray[i];
        //FS_LOGI("Calling get Device: %p, %u, %u",env,getDeviceMethodId,currentID);

        jobject currentInputDevice=env->CallStaticObjectMethod(inputDeviceClass,getDeviceMethodId,currentID);

        if(currentInputDevice)
        {
          //  FS_LOGI("found  Device");

            jclass deviceInstanceClass = env->GetObjectClass(currentInputDevice);
            if(!deviceInstanceClass)
            {
                FS_LOGI("deviceInstanceClass not found");
                continue;
            }
          //  FS_LOGI("calling getSources");
            jmethodID deviceSourcesMethodID = env->GetMethodID(deviceInstanceClass,"getSources","()I");

            if(!deviceSourcesMethodID)
            {
                FS_LOGI("device sources MethodID lookup failed");
                continue;
            }
            jmethodID deviceIsVirtualMethodID = env->GetMethodID(deviceInstanceClass,"isVirtual","()Z");

            if(!deviceIsVirtualMethodID)
            {
                FS_LOGI("device isVirtual MethodID lookup failed");
                continue;
            }
         //   FS_LOGI("Looking For Vaild Device");
            int sources = (int) env->CallIntMethod(currentInputDevice,deviceSourcesMethodID);
            if (((sources & InputDevice_SOURCE_GAMEPAD) == InputDevice_SOURCE_GAMEPAD)
                           || ((sources & InputDevice_SOURCE_JOYSTICK)
                           == InputDevice_SOURCE_JOYSTICK) || ((sources & InputDevice_SOURCE_DPAD)
                           == InputDevice_SOURCE_DPAD))
            {
                bool isvirtual = (bool) env->CallBooleanMethod(currentInputDevice,deviceIsVirtualMethodID);
                jmethodID deviceNameMethodID = env->GetMethodID(deviceInstanceClass,"getName","()Ljava/lang/String;");

                if(!deviceNameMethodID)
                {
                        FS_LOGI("device sources getName lookup failed");
                        continue;

                }
                 jstring nameString = (jstring) env->CallObjectMethod(currentInputDevice,deviceNameMethodID);
                 const char * str = env->GetStringUTFChars(nameString, NULL);
                 std::string nameOfJoystick = str;
                 FS_LOGI("Found name of controller %s",str);
                 env->ReleaseStringUTFChars(nameString, str);

                if(!isvirtual && nameOfJoystick.find("HDMI")==std::string::npos && nameOfJoystick.find("amazon-cec")==std::string::npos )
                {
                   FS_LOGI("Vaild Device in c++ %i index number %i",devicesArray[i],i);
                   foundJoysticks.push_back(currentID);
                   std::vector<jint>::iterator itr = std::find(currentAttachedJoysticks.begin(), currentAttachedJoysticks.end(), currentID);
                   if(itr != currentAttachedJoysticks.end())
                   {
                       FS_LOGI("Found in c++ %i in current joysticks",devicesArray[i]);

                       currentAttachedJoysticks.erase(itr);
                   }
                }
            }
            env->DeleteLocalRef(deviceInstanceClass);
            env->DeleteLocalRef(currentInputDevice);
        }
        FS_LOGI("currentAttachedJoysticks size %i ",currentAttachedJoysticks.size());
        for(std::vector<jint>::iterator itr = currentAttachedJoysticks.begin(); itr != currentAttachedJoysticks.end();++itr)
        {
            JNIBridge::update(*itr,UpdateType::removedDevice,jvm);
        }
        FS_LOGI("foundJoysticks size %i ",foundJoysticks.size());

        for(std::vector<jint>::iterator itr = foundJoysticks.begin(); itr != foundJoysticks.end();++itr)
        {
            JNIBridge::update(*itr,UpdateType::addedDevice,jvm);
        }
        currentAttachedJoysticks.clear();
        currentAttachedJoysticks = foundJoysticks;


    }
    env->ReleaseIntArrayElements(*deviceIdArray, devicesArray, JNI_ABORT);
    env->DeleteLocalRef(deviceIdsObj);


}
