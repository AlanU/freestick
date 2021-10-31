#include "USB/platform/MacOSX/FSMacUtil.h"
#include <unordered_map>

std::unordered_map<std::string,int> connectedContorllers;
std::unordered_map<std::string,uint32_t> identifierToVPIDContorllers;
void connectKnownControllers(const std::string & name)
{
    connectedContorllers[name]++;
}

void dissconnectKnownControllers(const std::string & name)
{
    connectedContorllers[name]-- ;
    if(connectedContorllers[name] <= 0 )
    {
        connectedContorllers.erase(name);
    }
}

bool containsControler(const std::string & name)
{
    return connectedContorllers.find(name) != connectedContorllers.end();
}


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
