#pragma once

#include "../../FSUSBJoystickDeviceManager.h"
#include "jni_wrapper.h"
namespace freestick
{
    class FSHIDAndroidJoysickDeviceManager : public FSUSBJoystickDeviceManager , IJINICallBack
    {
    public:
        FSHIDAndroidJoysickDeviceManager();
        virtual void init( );
        virtual void gamepadWasAddedFromJINBridge(int hid_id);
        virtual void gamepadWasRemovedFromJINBridge(int hid_id);
    protected:
        virtual void addDevice(FSBaseDevice * device);
        virtual void removeDevice(FSBaseDevice * device);
        virtual void addDevice(int  hid_deviceID);
        virtual void removeDevice(int hid_deviceID);

    };
}
