#if  ! __has_feature(objc_arc)
    #error This file must be compiled with ARC. Use -fobjc-arc flag (or convert project to ARC).
#endif
#include "USB/platform/MacOSX/FSMacUtil.h"
#include "USB/common/FSUSBJoystickDeviceManager.h"
#include <unordered_map>
#import "USB/platform/MacOSX/GCController+hidServices.h"
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/hid/IOHIDLib.h>

typedef struct CF_BRIDGED_TYPE(id) __IOHIDServiceClient * IOHIDServiceClientRef;
extern "C" CFTypeRef _Nullable IOHIDServiceClientCopyProperty(IOHIDServiceClientRef service, CFStringRef key);
std::unordered_map<std::string,uint32_t> identifierToVPIDContorllers;
freestick::IMuitControllerManager * iMuitManager = nullptr; //Does not own memeory
void connectUniqueIDControllers(const std::string & identifier, u_int32_t vendorAndProductID)
{
    identifierToVPIDContorllers[identifier] = vendorAndProductID;
}

void dissconnectUniqueIDControllers(const std::string & identifier)
{
      identifierToVPIDContorllers.erase(identifier);
}

std::pair<bool,uint32_t> getVendorAndProductFromUniqueID(const std::string & identifier)
{
    uint32_t vpId = 0;
    bool vaild = false;
    if( identifierToVPIDContorllers.find(identifier) != identifierToVPIDContorllers.end())
    {
        vaild = true;
        vpId = identifierToVPIDContorllers[identifier];
    }
    return std::pair<bool,uint32_t>(vaild,vpId);
}

bool isDeviceInOtherManagers(void * manager, freestick::vendorIDType vendorID, freestick::productIDType prodcutID)
{
    if(iMuitManager != nullptr)
    {
        return iMuitManager->isDeviceInOtherManagers( manager,  vendorID, prodcutID);
    }
    else
    {
        return false;
    }
}

bool removeDeviceFromManagers(freestick::vendorIDType vendorID, freestick::productIDType prodcutID)
{
    if(iMuitManager != nullptr)
    {
        return iMuitManager->removeDeviceFromManagers(vendorID, prodcutID);
    }
    else
    {
        return false;
    }
}

void setManger(freestick::IMuitControllerManager * manager)
{
    iMuitManager = manager;
}

void unSetManger()
{
    iMuitManager = nullptr;
}

std::pair<bool,uint32_t> getVendroAndProductID(const void * controller)
{
    uint16_t vendorID = 0;
    uint16_t productID = 0;
    GCController * gccontroller = static_cast<GCController*>(CFBridgingRelease(controller));
    controller = nullptr;
    for (_GCCControllerHIDServiceInfo *serviceInfo in gccontroller.hidServices) {
        if (serviceInfo.service)
        {
                int vendorInt = 0 ;
                int productInt = 0;
                CFNumberRef vendor = static_cast<CFNumberRef>(IOHIDServiceClientCopyProperty(serviceInfo.service, CFSTR(kIOHIDVendorIDKey)));
                if (vendor)
                {
                    CFNumberGetValue(vendor, kCFNumberSInt32Type, &vendorInt);
                    vendorID = vendorInt;
                    CFRelease(vendor);
                }

                CFNumberRef product = static_cast<CFNumberRef>(IOHIDServiceClientCopyProperty(serviceInfo.service, CFSTR(kIOHIDProductIDKey)));
                if (product)
                {
                    CFNumberGetValue(product, kCFNumberSInt32Type, &productInt);
                    productID = productInt;
                    CFRelease(product);
                }
                return std::pair<bool,uint32_t>(true,freestick::FSUSBJoystickDeviceManager::createIdForElement(vendorID,productID));
        }
    }
    return std::pair<bool,uint32_t>(false,0);
}

bool isMFISupported()
{
    bool mfi = false;
    if(@available(macOS 10.9, *))
    {
        mfi = true;
    }
    return mfi;
}
