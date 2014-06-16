#pragma once

#include <jni.h>

#ifdef __cplusplus
#include <vector>
extern "C" {
#endif
    JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadWasAdded(JNIEnv *env, jobject thisObj,jint HID_ID);
    JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadWasRemoved(JNIEnv *env, jobject thisObj,jint HID_ID);
#ifdef __cplusplus
}
class IJINICallBack
{
public:
    virtual void gamepadWasAddedFromJINBridge(int hid_id) = 0;
    virtual void gamepadWasRemovedFromJINBridge(int hid_id) = 0;
};

class JNIBridge
{
    public:
       static void registerDeviceWasAdded(IJINICallBack * listener);
       static void registerDeviceWasRemoved(IJINICallBack * listener){}
       static void deregisterDeviceWasAdded(IJINICallBack * listener){}
       static void deregisterDeviceWasRemoved(IJINICallBack * listener){}
       static void update(int hidDeviceID, int type);
    private:
        static std::vector<IJINICallBack*> _deviceAddedCallback;
        static std::vector<IJINICallBack*> _deviceRemovedCallback;
};
#endif
