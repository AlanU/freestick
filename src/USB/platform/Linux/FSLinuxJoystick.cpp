#include "USB/platform/Linux/FSLinuxJoystick.h"
#include <utility>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace freestick;


static std::vector<std::pair<uint16_t,uint16_t>> supportedButtonCodes{

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
    {BTN_THUMB,EV_KEY},
    {BTN_THUMB2,EV_KEY},
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
    {ABS_TILT_Y,EV_ABS},
    {MSC_SCAN,EV_MSC}

};
//EV_KEY
/*    REL_X,
    REL_y,
    REL_Z,8?*/
// Lookup table for mapping combined keys to HID Usage/Page

// Function to convert event type and code to HID Usage and Usage Page
FSLinuxJoystick::HIDMapping FSLinuxJoystick::getHIDUsageAndPage(uint16_t event_type, uint16_t event_code)
{
    static auto eventToHIDMap = createEventToHIDMapping();

    // Create the key by combining event_type and event_code
    uint32_t key = makeKey(event_type, event_code);

    auto it = eventToHIDMap.find(key);
    if (it != eventToHIDMap.end()) {
        const HIDMapping hid = it->second;
        return hid;
    }

    return HIDMapping{};
}

int32_t FSLinuxJoystick::getDpadDeviceInput(uint16_t type, uint16_t code, int32_t value)
{
    FSDeviceInput dpadInput = Unknown;

    if( (code == ABS_HAT0X || code == ABS_HAT0Y))
    {
        std::cout<<"Looking value DPad"<<m_isMapped<<std::endl;

        if (code == ABS_HAT0X) {
            switch(value){
            case -1:
                dpadInput = DPadLeft;
            break;
            case 1:
                   dpadInput = DPadRight;
            break;
            case 0:
                dpadInput = LastValueUp;
            break;

            }
        }
        else if(code == ABS_HAT0Y)
        {
            switch(value){
            case -1:
                dpadInput = DPadUp;
                break;
            case 1:
                dpadInput = DPadDown;
                break;
            case 0:
                dpadInput = LastValueUp;
                break;

            }
        }
        if(m_isHatSwitchDpad)
        {
            FSUSBElementInfoMap dpadMap = m_usbJoystickManager->infoMapForInputType(_vendorID,_productID,dpadInput);
            if(dpadMap.getDeviceInput() != LastInput)
            {
                return dpadMap.getMin();
            }
            else
            {
                return value;
            }
        }
    }
    return value;
    //TODO return something better than value on error
}

FSLinuxJoystick::FSLinuxJoystick(idNumber joyStickID,
                                 const std::string & devicePath,
                                 vendorIDType vendorID,
                                 productIDType productID,
                                 FSUSBJoystickDeviceManager & usbJoystickManager):FSUSBJoystick(joyStickID,0,0,0,false,vendorID,productID)
//Note do not hold on to the openDevHandel it will be closed after this call
{

    //Check how dpad works
    m_usbJoystickManager = &usbJoystickManager;

    std::cout << "FSLinuxJoystick"<<std::endl;

        m_devicePath=devicePath;
        m_openFileHandler=-1;
        m_evdevHandel=nullptr ;
        // Open the device file
        m_openFileHandler = open(m_devicePath.c_str(), O_RDONLY | O_NONBLOCK);
        if (m_openFileHandler < 0) {
            perror(("Failed to open device: " + m_devicePath).c_str());
            return; // Exit the constructor if the file cannot be opened
        }
        std::cout << "Initialize libevdev"<<std::endl;

        // Initialize libevdev
        int handRe = libevdev_new_from_fd(m_openFileHandler, &m_evdevHandel);
        if (handRe < 0 || m_evdevHandel == nullptr) {
            perror(("Failed to initialize libevdev for device: " + m_devicePath).c_str());
            close(m_openFileHandler); // Clean up the file descriptor
            m_openFileHandler = -1;
            return; // Exit if libevdev initialization fails
        }

        // Retrieve the device name
        const char* deviceName = libevdev_get_name(m_evdevHandel);
        if (deviceName) {
            _vendorIDFriendlyName = std::string(deviceName);
        } else {
            _vendorIDFriendlyName = "Unknown Device";
        }
        std::cout << "supportedButtonCodes"<<std::endl;

    for(std::pair<uint16_t,uint16_t> & code : supportedButtonCodes)
    {
        if (libevdev_has_event_code(m_evdevHandel, code.second,code.first))
        {
            //        FSUSBJoyStickInputElement(unsigned int id, unsigned int parentID, minMaxNumber elementMin, minMaxNumber elementMax, vendorIDType vendorID,productIDType productID,FSUSBDeviceManager & _manager,physicalValueNumber currentValue,minMaxNumber buttonNumber);
           // FSUSBJoyStickInputElement(unsigned int id, unsigned int parentID, minMaxNumber elementMin, minMaxNumber elementMax, vendorIDType vendorID,productIDType productID,FSUSBDeviceManager * _manager,physicalValueNumber currentValue,minMaxNumber buttonNumber);
            minMaxNumber min = 0;
            minMaxNumber max = 1;
            if(EV_ABS == code.second)
            {
                min =  libevdev_get_abs_minimum(m_evdevHandel,code.first);
                max = libevdev_get_abs_maximum(m_evdevHandel,code.first);
            }
            HIDMapping codeHid = getHIDUsageAndPage(code.second,code.first);
            if(codeHid.usage_page != 0 && codeHid.usage != 0)
            {
                FSUSBJoyStickInputElement temp(FSUSBJoystickDeviceManager::createIdForElement(codeHid.usage,codeHid.usage_page), getJoystickID() ,min,max, _vendorID,_productID,usbJoystickManager,0,0);
                addInputElement(temp);
            }
            else
            {
                printf("No Hid for: %s %s\n",
                       libevdev_event_type_get_name(code.second),
                       libevdev_event_code_get_name(code.second, code.first));
            }
        }
        else
        {
            printf("No support for event code for: %s %s\n",
                   libevdev_event_type_get_name(code.second),
                   libevdev_event_code_get_name(code.second, code.first));
        }
    }

    HIDMapping key= createEventToHIDMapping()[makeKey(EV_ABS, ABS_HAT0X)];
    auto hidKey = FSUSBDeviceManager::createVPId(key.usage,key.usage_page);
    m_isHatSwitchDpad = usbJoystickManager.doesElementHaveDeviceInputForValue(vendorID,productID,hidKey,LastValueUp);
     m_isMapped = usbJoystickManager.doesDeviceHaveDeviceInput(getJoystickID(),Button0);
    std::cout << "FSLinuxJoystick end"<<std::endl;


}

FSLinuxJoystick::~FSLinuxJoystick()
{
    close(m_openFileHandler); //This conflicts with file loop TODO figure this out
    libevdev_free(m_evdevHandel);
    m_evdevHandel= nullptr;
}

libevdev * FSLinuxJoystick::getHandel()
{
    return m_evdevHandel;
}




