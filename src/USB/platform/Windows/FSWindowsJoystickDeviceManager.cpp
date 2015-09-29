#include "USB/platform/Windows/FSWindowsJoystickDeviceManager.h"
using namespace freestick;
FSWindowsJoystickDeviceManager::FSWindowsJoystickDeviceManager()
{
    _listeningForEvents = false;
}

void FSWindowsJoystickDeviceManager::ListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener)
{
    if(!_listeningForEvents)
    {
        _listeningForEvents = true;
    _directInputDeviceManager.ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                        FS_JOYSTICK_DISCONNECT_EVENT |
                                                        FS_BUTTON_EVENT | FS_AXIS_EVENT
                                                        | FS_TRIGGER_EVENT,*this);
    _xInputDeviceManger.ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                        FS_JOYSTICK_DISCONNECT_EVENT |
                                                        FS_BUTTON_EVENT | FS_AXIS_EVENT
                                                        | FS_TRIGGER_EVENT,*this);
    }

     FSUSBJoystickDeviceManager::ListenForAllJoysticksForEventTypes(eventFlags,listener);
}

void FSWindowsJoystickDeviceManager::init( )
{
   FSBaseManager * basManagerPtr = &_directInputDeviceManager;
   basManagerPtr->init(this);
   basManagerPtr = &_xInputDeviceManger;
   basManagerPtr->init(this);
}

void FSWindowsJoystickDeviceManager::update()
{
    _directInputDeviceManager.update();
    _xInputDeviceManger.update();
}

const FSBaseDevice * FSWindowsJoystickDeviceManager::getDevice(DeviceID deviceID)
{
   const FSBaseDevice * device = _xInputDeviceManger.getDevice(deviceID);
    if(device == NULL)
    {
        return _directInputDeviceManager.getDevice(deviceID);
    }
    else
    {
        return device;
    }
}

DeviceID FSWindowsJoystickDeviceManager::getNextID()
{
    return FSUSBJoystickDeviceManager::getNextID();
}


void FSWindowsJoystickDeviceManager::onButtonDown(FSDeviceInputEvent event)
{
    FSUSBJoystickDeviceManager::updateEvent(event);
}

void FSWindowsJoystickDeviceManager::onButtonUp(FSDeviceInputEvent event)
{
    FSUSBJoystickDeviceManager::updateEvent(event);
}

void FSWindowsJoystickDeviceManager::onStickMove(FSDeviceInputEvent event)
{
    FSUSBJoystickDeviceManager::updateEvent(event);
}

void FSWindowsJoystickDeviceManager::onDisconnect(FSBaseEvent event)
{
    FSUSBJoystickDeviceManager::updateEvent(event);
}

void FSWindowsJoystickDeviceManager::onConnect(FSBaseEvent event)
{
    FSUSBJoystickDeviceManager::updateEvent(event);
}
