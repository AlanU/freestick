#include "jni_wrapper.h"
std::vector<IJINICallBack*> JNIBridge::_deviceAddedCallback;
std::vector<IJINICallBack*> JNIBridge::_deviceRemovedCallback;
JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadWasAdded(JNIEnv *env, jobject thisObj,jint HID_ID)
{
  //  gamepadWasAdded(devicemanager,HID_ID);
    JNIBridge::update(HID_ID,0);
}

JNIEXPORT void JNICALL Java_org_freestick_FreestickDeviceManager_gamepadWasRemoved(JNIEnv *env, jobject thisObj,jint HID_ID)
{
   //gamepadWasRemoved(devicemanager,HID_ID);
    JNIBridge::update(HID_ID,1);

}

void JNIBridge::update(int hidDeviceID, int type)
{
    int t=hidDeviceID;
    switch(type)
    {
        case 0:
            //run through the _devieAddedCallback map cand call the correct function
        break;
    }
}

void JNIBridge::registerDeviceWasAdded(IJINICallBack *listener)
{
    _deviceAddedCallback.push_back(listener);
}
