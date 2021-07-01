#include "USB/platform/Windows/FSWindowsJoystickDeviceManager.h"
//direct input
#include "USB/platform/Windows/FSDirectInputJoystickManager.h"

//Xinput
#include "USB/platform/Windows/FSXInputJoystickDeviceManager.h"

using namespace freestick;

FSWindowsJoystickDeviceManager::FSWindowsJoystickDeviceManager()
{
   managers.reserve(2);
   managers.push_back(unique_ptr_of_managers (new FSDirectInputJoystickManager));
   managers.push_back(unique_ptr_of_managers (new FSXInputJoystickDeviceManager));
}



