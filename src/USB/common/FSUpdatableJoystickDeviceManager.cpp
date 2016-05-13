#include "USB/common/FSUpdatableJoystickDeviceManager.h"
using namespace freestick;
FSUpdatableJoystickDeviceManager::FSUpdatableJoystickDeviceManager()
{

}

void FSUpdatableJoystickDeviceManager::update()
{

}

void FSUpdatableJoystickDeviceManager::updateEvents(unsigned int joystickDeviceID, FSUSBJoyStickInputElement * elementDevice, PhysicalValueNumber elementValue)
{
	if (elementDevice->getValue() != elementValue) {

		if (elementDevice->isIntialized())
		{
			FSUSBJoystickDeviceManager::updateEvents(joystickDeviceID, elementDevice, elementValue);
		}
		else
		{
			std::stack<FSUSBElementInfoMap> inputTypes;
			elementDevice->getMapping(elementValue, inputTypes);
		}
	}
}