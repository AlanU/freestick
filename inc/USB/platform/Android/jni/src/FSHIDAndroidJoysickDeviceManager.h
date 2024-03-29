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
#include "USB/common/FSUSBJoystickDeviceManager.h"
#include "FSJNI_Wrapper.h"
#include "common/FSTypes.h"
#include <jni.h>
#include <map>
namespace freestick
{
    class FSHIDAndroidJoysickDeviceManager : public FSUSBJoystickDeviceManager , IJNICallBack
    {
    public:
        FSHIDAndroidJoysickDeviceManager();
        ~FSHIDAndroidJoysickDeviceManager() override;
        void init(JavaVM * jvm);
        virtual void init();
        virtual void gamepadWasAddedFromJINBridge(int hid_id,JavaVM * jvm);
        virtual void gamepadWasRemovedFromJINBridge(int hid_id);
        virtual bool gamepadWasUpdatedFromJINBridge(int deviceid,int code,JNICallBackType type,float value,minMaxNumber min,minMaxNumber max);
        void addAndroidMapping(unsigned int androidEventType,FSDeviceInput deviceInput);
        void update();
    private:
        std::map<int,elementID> _androidIDToIDMap;
        //Requires two maps since motion events and key events defines collide
        std::map<unsigned int,FSDeviceInput > _androidButtonUsageMapToInputEvent;//KeyEvents
        std::map<unsigned int,FSDeviceInput > _androidAxisnUsageMapToInputEvent;//MotionEvents

        JNIEnv *_jniEvn ;
        JavaVM * _jvm;


    };
}
