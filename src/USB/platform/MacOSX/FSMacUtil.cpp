#include "USB/platform/MacOSX/FSMacUtil.h"
#include <unordered_map>

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
