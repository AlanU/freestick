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

#include "USB/platform/Android/jni/src/FSAndroidJoystick.h"
#include <android/log.h>
#include <android/input.h>
#define FS_LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "freestick", __VA_ARGS__))
#define FS_LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "freestick", __VA_ARGS__))

#include <jni.h>
using namespace freestick;
FSAndroidJoystick::FSAndroidJoystick(int androidDeviceID,
                                    unsigned int joyStickID,
                                    unsigned int numberOfButtons,
                                    unsigned int numberOfAnlogSticks,
                                    unsigned int numberOfDigitalSticks,
                                    bool forceFeedBackSupported,JavaVM * jvm ):FSUSBJoystick(joyStickID,
                                                                                numberOfButtons,
                                                                                numberOfAnlogSticks,
                                                                                numberOfDigitalSticks,
                                                                                forceFeedBackSupported,
                                                                                -1,
                                                                                -1 )

{

    _androidDeviceID = androidDeviceID;
    JNIEnv *env;
    //TODO cache jclass and methodID
#ifdef JDK1_4
    jvm->AttachCurrentThread((void**)(&env),NULL);
#else
    //Old jdk pre 1.4
    jvm->AttachCurrentThread(&env,NULL);
#endif
    jclass inputDeviceClass = env->FindClass("android/view/InputDevice");
    bool error = false;
    if(!inputDeviceClass)
    {
        FS_LOGI("call from updateJoysticks class not found");
        error = true;
    }

    jmethodID getDeviceMethodId = env->GetStaticMethodID(inputDeviceClass,"getDevice","(I)Landroid/view/InputDevice;");
    if(!getDeviceMethodId)
    {
        FS_LOGI("get device MethodID lookup failed");
        error = true;
    }
    jobject currentInputDevice=env->CallStaticObjectMethod(inputDeviceClass,getDeviceMethodId,androidDeviceID);

    if(currentInputDevice)
    {
        jclass deviceInstanceClass = env->GetObjectClass(currentInputDevice);
        if(!deviceInstanceClass)
        {
            FS_LOGI("deviceInstanceClass not found");
            error = true;
        }

        jmethodID deviceNameMethodID = env->GetMethodID(deviceInstanceClass,"getName","()Ljava/lang/String;");

        if(!deviceNameMethodID)
        {
                FS_LOGI("device sources getName lookup failed");
                error = true;

        }
         jstring nameString = (jstring) env->CallObjectMethod(currentInputDevice,deviceNameMethodID);
         const char * str = env->GetStringUTFChars(nameString, NULL);
         _prodcutIDFriendlyName = str;
         FS_LOGI("Found name of controller %s",str);
         env->ReleaseStringUTFChars(nameString, str);

         /*Requires sdk 19 or greater
          * try
         {
            jmethodID deviceVendorIdMethodID = env->GetMethodID(deviceInstanceClass,"getVendorId","()I");

            if(!deviceVendorIdMethodID)
            {
                    FS_LOGI("device vendor id lookup failed");
                    error = true;

            }
            else
            {
                _vendorID = (long) env->CallIntMethod(currentInputDevice,deviceVendorIdMethodID);
            }
        }
        catch(int e){}
        try
        {
            jmethodID deviceProductIdMethodID = env->GetMethodID(deviceInstanceClass,"getProductId ","()I");

            if(!deviceProductIdMethodID)
            {
                    FS_LOGI("device product ID lookup failed");
                    error = true;

            }
            else
            {
                _productID = (long) env->CallIntMethod(currentInputDevice,deviceProductIdMethodID);
            }
        }
        catch(int e){}*/


         env->DeleteLocalRef(deviceInstanceClass);
         env->DeleteLocalRef(currentInputDevice);
    }


}

unsigned int FSAndroidJoystick::Init(FSUSBJoystickDeviceManager & usbJoystickManager)
{
    return 0;
}

