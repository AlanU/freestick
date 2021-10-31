#pragma once
#include <string>
void connectKnownControllers(const std::string & name);
void dissconnectKnownControllers(const std::string & name);
bool containsControler(const std::string & name);
void connectUniqueIDControllers(const std::string & identifier, u_int32_t vendorAndProductID);
void dissconnectUniqueIDControllers(const std::string & identifier);
std::pair<bool,uint32_t> getVendorAndProductFromUniqueID(const std::string & identifier);
