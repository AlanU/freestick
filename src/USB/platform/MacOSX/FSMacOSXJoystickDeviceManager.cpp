#include "USB/platform/MacOSX/FSMacOSXJoystickDeviceManager.h"
#include "USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.h"
#include "USB/platform/iOS/FSMFIJoystickManager.h"
using namespace freestick;

FSMacOSXJoystickDeviceManager::FSMacOSXJoystickDeviceManager()
{
   //TODO fix name of header file FSMFIJoystickDeviceManager
   managers.reserve(2);
   managers.push_back(unique_ptr_of_managers (new FSUSBMacOSXJoystickDeviceManager));
   managers.push_back(unique_ptr_of_managers (new FSMFIJoystickDeviceManager));
}

FSMacOSXJoystickDeviceManager::~FSMacOSXJoystickDeviceManager()
{
}

void FSMacOSXJoystickDeviceManager::update()
{

}
