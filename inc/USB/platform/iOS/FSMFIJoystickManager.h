#pragma once
#include "USB/common/FSUSBJoystickDeviceManager.h"
#include <map>
#include <vector>
namespace freestick
{
typedef int mfiID;
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
        void updateConnectedControllers();
        void updateControllers();
        void removeMFIDevice(mfiID device);
        void addMFIDevice(mfiID device, void * controller);
        void addMFIMapping();
       // uint64_t contorllerIDs = 0;
       std::vector<mfiID> _connectedLastUpdateJoysticks;
       std::map<mfiID,unsigned int> _wordToIDControllerMap;
    };
}
