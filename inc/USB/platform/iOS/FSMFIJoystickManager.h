#pragma once
#include "USB/common/FSUSBJoystickDeviceManager.h"

namespace freestick
{
    class FSMFIJoystickDeviceManager : public FSUSBJoystickDeviceManager
    {
    public:
        FSMFIJoystickDeviceManager();
        virtual ~FSMFIJoystickDeviceManager();
        virtual void init( );
        const FSUSBJoystick * getUSBJoystickDevice(idNumber deviceID){return static_cast<const FSUSBJoystick *>(FSUSBDeviceManager::getDevice(deviceID));}

    protected:
        void updateJoystickButtons(idNumber joyStickID, idNumber elementID, bool pressed,float value);
        void updateJoystickAnalog(idNumber joyStickID,idNumber elementID,float value);
        void updateControllers();
        void addMFIMapping();


    };
}
