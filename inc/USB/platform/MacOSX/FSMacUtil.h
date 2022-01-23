#pragma once
#include <string>
#include "Interfaces/IMuitControllerManager.h"
void connectUniqueIDControllers(const std::string & identifier, u_int32_t vendorAndProductID);
void dissconnectUniqueIDControllers(const std::string & identifier);
std::pair<bool,uint32_t> getVendorAndProductFromUniqueID(const std::string & identifier);
bool isDeviceInOtherManagers(void * manager, freestick::vendorIDType vendorID, freestick::productIDType prodcutID);
bool removeDeviceFromManagers(freestick::vendorIDType vendorID, freestick::productIDType prodcutID);
void setManger(freestick::IMuitControllerManager * manager);
void unSetManger();
std::pair<bool,uint32_t> getVendroAndProductID(const void * controller);
bool isMFISupported();
