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

#pragma once

#include <jni.h>
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
typedef enum
{
    JoystickAdded = 0,
    JoystickRemoved =1,
    KeyEvent = 2,
    MotionEvent = 3
}JNICallBackType;
#ifdef __cplusplus
#include <vector>
extern "C" {
#endif
    JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadWasAdded(JNIEnv *env, jobject thisObj,jint HID_ID);
    JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadWasRemoved(JNIEnv *env, jobject thisObj,jint HID_ID);
    JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadDeviceUpdate(JNIEnv *env, jobject thisObj,jint deviceid,jint code,jint type,jfloat value,jint min,jint max);

#ifdef __cplusplus
}
class IJINICallBack
{
public:
    virtual void gamepadWasAddedFromJINBridge(int hid_id,JavaVM * jvm) = 0;
    virtual void gamepadWasRemovedFromJINBridge(int hid_id) = 0;
    virtual void gamepadWasUpdatedFromJINBridge(int deviceid,int code,JNICallBackType type,float value,int min,int max) = 0;
};

class JNIBridge
{
    public:
        //TODO use flag to make this all the register call backs two functions
       static void registerDeviceWasAdded(IJINICallBack * listener);
       static void registerDeviceWasRemoved(IJINICallBack * listener);
       static void registerDeviceWasUpdated(IJINICallBack * listener);
       static void deregisterDeviceWasAdded(IJINICallBack * listener){}
       static void deregisterDeviceWasRemoved(IJINICallBack * listener){}
       static void update(int hidDeviceID, int type);
       static void update(int hidDeviceID, int type,JavaVM * jvm);
       static void updateValue(int deviceid,int code,JNICallBackType type,float value,int min,int max);
       static void updateJoysticks(JavaVM * jvm);
    private:
        static std::vector<IJINICallBack*> _deviceAddedCallback;
        static std::vector<IJINICallBack*> _deviceRemovedCallback;
        static std::vector<IJINICallBack*> _deviceUpdateCallback;
};
#endif
