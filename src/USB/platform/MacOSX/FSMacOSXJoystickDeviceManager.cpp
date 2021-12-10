#include "USB/platform/MacOSX/FSMacOSXJoystickDeviceManager.h"
#include "USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.h"
#include "USB/platform/iOS/FSMFIJoystickManager.h"
#include "USB/platform/MacOSX/FSMacUtil.h"
using namespace freestick;

FSMacOSXJoystickDeviceManager::FSMacOSXJoystickDeviceManager()
{
   //TODO fix name of header file FSMFIJoystickDeviceManager
   FSUSBMacOSXJoystickDeviceManager * macLegacy  = new FSUSBMacOSXJoystickDeviceManager;
   setManger(macLegacy);
   managers.reserve(2);
   managers.push_back(unique_ptr_of_managers (new FSMFIJoystickDeviceManager));
   managers.push_back(unique_ptr_of_managers (macLegacy));
   macLegacy = nullptr;

}

FSMacOSXJoystickDeviceManager::~FSMacOSXJoystickDeviceManager()
{
    unSetManger();
}

void FSMacOSXJoystickDeviceManager::update()
{

}
