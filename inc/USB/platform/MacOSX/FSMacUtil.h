#pragma once
#include <string>
void connectUniqueIDControllers(const std::string & identifier, u_int32_t vendorAndProductID);
void dissconnectUniqueIDControllers(const std::string & identifier);
std::pair<bool,uint32_t> getVendorAndProductFromUniqueID(const std::string & identifier);
