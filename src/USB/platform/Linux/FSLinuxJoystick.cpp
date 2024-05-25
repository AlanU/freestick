#include "USB/platform/Linux/FSLinuxJoystick.h"
#include <utility>
#include <vector>
#include <unistd.h>

using namespace freestick;

static std::vector<std::pair<unsigned int,unsigned int>> supportedButtonCodes{

    {BTN_MISC,EV_KEY},
    {BTN_0,EV_KEY},
    {BTN_1,EV_KEY},
    {BTN_2,EV_KEY},
    {BTN_3,EV_KEY},
    {BTN_4,EV_KEY},
    {BTN_5,EV_KEY},
    {BTN_6,EV_KEY},
    {BTN_7,EV_KEY},
    {BTN_8,EV_KEY},
    {BTN_MOUSE,EV_KEY},
    {BTN_LEFT,EV_KEY},
    {BTN_RIGHT,EV_KEY},
    {BTN_MIDDLE,EV_KEY},
    {BTN_SIDE,EV_KEY},
    {BTN_EXTRA,EV_KEY},
    {BTN_FORWARD,EV_KEY},
    {BTN_BACK,EV_KEY},
    {BTN_TASK,EV_KEY},
    {BTN_JOYSTICK,EV_KEY},
    {BTN_TRIGGER,EV_KEY},
    {BTN_THUMB,EV_KEY},
    {BTN_THUMB2,EV_KEY},
    {BTN_TOP,EV_KEY},
    {BTN_TOP2,EV_KEY},
    {BTN_BASE,EV_KEY},
    {BTN_BASE2,EV_KEY},
    {BTN_BASE3,EV_KEY},
    {BTN_BASE4,EV_KEY},
    {BTN_BASE5,EV_KEY},
    {BTN_BASE6,EV_KEY},
    {BTN_DEAD,EV_KEY},

    {BTN_GAMEPAD,EV_KEY},
    {BTN_SOUTH,EV_KEY},
    {BTN_EAST,EV_KEY},
    {BTN_C,EV_KEY},
    {BTN_NORTH,EV_KEY},
    {BTN_WEST,EV_KEY},
    {BTN_Z,EV_KEY},
    {BTN_TL,EV_KEY},
    {BTN_TR,EV_KEY},
    {BTN_TL2,EV_KEY},
    {BTN_TR2,EV_KEY},
    {BTN_SELECT,EV_KEY},
    {BTN_START,EV_KEY},
    {BTN_MODE,EV_KEY},
    {BTN_THUMBL,EV_KEY},
    {BTN_THUMBR,EV_KEY},
    {BTN_DIGI,EV_KEY},
    {BTN_WHEEL,EV_KEY},
    {BTN_GEAR_DOWN,EV_KEY},
    {BTN_GEAR_UP,EV_KEY},

    {ABS_Z,EV_ABS},
    {ABS_X,EV_ABS},
    {ABS_Y,EV_ABS},
    {ABS_Z,EV_ABS},
    {ABS_RX,EV_ABS},
    {ABS_RY,EV_ABS},
    {ABS_RZ,EV_ABS},
    {ABS_THROTTLE,EV_ABS},
    {ABS_RUDDER,EV_ABS},
    {ABS_WHEEL,EV_ABS},
    {ABS_GAS,EV_ABS},
    {ABS_BRAKE,EV_ABS},
    {ABS_HAT0X,EV_ABS},
    {ABS_HAT0Y,EV_ABS},
    {ABS_HAT1X,EV_ABS},
    {ABS_HAT1Y,EV_ABS},
    {ABS_HAT2X,EV_ABS},
    {ABS_HAT2Y,EV_ABS},
    {ABS_HAT3X,EV_ABS},
    {ABS_HAT3Y,EV_ABS},
    {ABS_PRESSURE,EV_ABS},
    {ABS_DISTANCE,EV_ABS},
    {ABS_TILT_X,EV_ABS},
    {ABS_TILT_Y,EV_ABS}

};
//EV_KEY
/*    REL_X,
    REL_y,
    REL_Z,8?*/

FSLinuxJoystick::FSLinuxJoystick(idNumber joyStickID,
                                 libevdev * openDevHandel,
                                 int openFileHandler,
                                 const std::string & devicePath,
                                 vendorIDType vendorID,
                                 productIDType productID,
                                 FSUSBJoystickDeviceManager & usbJoystickManager):FSUSBJoystick(joyStickID,0,0,0,false,vendorID,productID)
//Note do not hold on to the openDevHandel it will be closed after this call
{

   // get device name libevdev_get_uniq
    _devicePath = devicePath;
    _evdevHandel = openDevHandel;
    _openFileHandler = _openFileHandler;
    if(_evdevHandel != nullptr)
    {
        //std::string _vendorIDFriendlyName;
       // std::string _productIDFriendlyName
        _vendorIDFriendlyName = libevdev_get_name(_evdevHandel); //TODO look up how to get the product name and vender name sepriate
    }

    for(auto code : supportedButtonCodes)
    {
        if (libevdev_has_event_code(_evdevHandel, code.second,code.first))
        {
            //        FSUSBJoyStickInputElement(unsigned int id, unsigned int parentID, minMaxNumber elementMin, minMaxNumber elementMax, vendorIDType vendorID,productIDType productID,FSUSBDeviceManager & _manager,physicalValueNumber currentValue,minMaxNumber buttonNumber);
           // FSUSBJoyStickInputElement(unsigned int id, unsigned int parentID, minMaxNumber elementMin, minMaxNumber elementMax, vendorIDType vendorID,productIDType productID,FSUSBDeviceManager * _manager,physicalValueNumber currentValue,minMaxNumber buttonNumber);
            minMaxNumber min = 0;
            minMaxNumber max = 1;
            if(EV_ABS == code.second)
            {
                min =  libevdev_get_abs_minimum(_evdevHandel,code.first);
                max = libevdev_get_abs_maximum(_evdevHandel,code.first);
            }
            FSUSBJoyStickInputElement temp(FSUSBJoystickDeviceManager::createIdForElement(code.first,code.second), getJoystickID() ,min,max, _vendorID,_productID,usbJoystickManager,0,0);
            addInputElement(temp);
        }
    }


}

FSLinuxJoystick::~FSLinuxJoystick()
{
    libevdev_free(_evdevHandel);
    close(_openFileHandler);
}

libevdev * FSLinuxJoystick::getHandel()
{
    return _evdevHandel;
}

