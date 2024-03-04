#include "USB/platform/Linux/FSLinuxJoystick.h"

using namespace freestick;

FSLinuxJoystick::FSLinuxJoystick(idNumber joyStickID,
                                 libevdev * openDevHandel,
                                 const std::string & devicePath,
                                 vendorIDType vendorID,
                                 productIDType productID):FSUSBJoystick(joyStickID,0,0,0,false,vendorID,productID)
//Note do not hold on to the openDevHandel it will be closed after this call
{
    _devicePath = devicePath;
    if(openDevHandel != nullptr)
    {
        //std::string _vendorIDFriendlyName;
       // std::string _productIDFriendlyName
        _vendorIDFriendlyName = libevdev_get_name(openDevHandel); //TODO look up how to get the product name and vender name sepriate
    }

}

