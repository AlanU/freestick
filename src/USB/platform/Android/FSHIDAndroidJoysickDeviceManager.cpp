#include "FSHIDAndroidJoysickDeviceManager.h"
#include "../NULL/FSUSBNullDevice.h"
#include "./jni_wrapper.h"
using namespace freestick;
FSHIDAndroidJoysickDeviceManager::FSHIDAndroidJoysickDeviceManager()
{
}



void FSHIDAndroidJoysickDeviceManager::init( )
{
    FSUSBDeviceManager::init();

    JNIBridge::registerDeviceWasAdded(this);
}



void FSHIDAndroidJoysickDeviceManager::gamepadWasAddedFromJINBridge(int deviceID)
{

   this->addDevice(deviceID);
}

void FSHIDAndroidJoysickDeviceManager::gamepadWasRemovedFromJINBridge(int deviceID)\
{

}


void FSHIDAndroidJoysickDeviceManager::addDevice(FSBaseDevice * device)
{
    FSUSBDeviceManager::addDevice(device);
}

void FSHIDAndroidJoysickDeviceManager::removeDevice(FSBaseDevice * device)
{

}

void FSHIDAndroidJoysickDeviceManager::addDevice(int  hid_deviceID)
{

    FSUSBNullDevice * newDevice = new FSUSBNullDevice();
    addDevice(newDevice);
}

void FSHIDAndroidJoysickDeviceManager::removeDevice(int hid_deviceID)
{

}

