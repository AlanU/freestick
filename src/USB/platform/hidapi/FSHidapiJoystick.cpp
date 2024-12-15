#include "USB/platform/hidapi/FSHidapiJoystick.h"
#include <utility>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <iomanip>

using namespace freestick;

static std::vector<std::pair<unsigned int,unsigned int>> supportedButtonCodes{};


// Utility to print a buffer in hexadecimal format
void printHex(const std::vector<unsigned char>& buffer) {
    for (const auto& byte : buffer) {
        std::cout << std::hex << std::setfill('0') << std::setw(2)
                  << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl; // Switch back to decimal formatting
}

void getGamepadFeatures(hid_device* device) {
    // Open the HID device
    if (!device) {
        std::cerr << "Failed to open the device"<<std::endl;
        return;
    }
    std::cout << "Device opened successfully." << std::endl;

    // Example feature report ID (replace with the correct one for your gamepad)
    unsigned char feature_report_id = 0x03;
    unsigned char feature_report[64] = {0}; // 64 bytes buffer
    feature_report[0] = feature_report_id;  // First byte is the report ID

    // Send a feature report
    int result = hid_send_feature_report(device, feature_report, sizeof(feature_report));
    if (result == -1) {
        std::cerr << "Failed to send feature report: " << hid_error(device) << std::endl;
    } else {
        std::cout << "Sent " << result << " bytes in the feature report." << std::endl;
    }

    // Get a feature report
    result = hid_get_feature_report(device, feature_report, sizeof(feature_report));
    if (result == -1) {
        std::cerr << "Failed to get feature report: " << hid_error(device) << std::endl;
    } else {
        std::cout << "Received feature report (" << result << " bytes):" << std::endl;
        std::vector<unsigned char> report_data(feature_report, feature_report + result);
        printHex(report_data);
    }

    // Close the device
    hid_close(device);
}



FSHIDAPIiJoystick::FSHIDAPIiJoystick(std::string_view devicePath,idNumber joyStickID):FSUSBJoystick(joyStickID,0,0,0,false,0,0)
{
    //#define MAX_STR 255
    //int res = 0;
   // unsigned char buf[65];
    //wchar_t wstr[MAX_STR];

    m_devicePath = devicePath;
    if (!m_devicePath.empty()) {
        m_handle = hid_open_path(m_devicePath.c_str());
        if(m_handle != nullptr)
        m_info = hid_get_device_info(m_handle); //TODO look up if this needs to be freed

    }
    if (m_info) {
        // Read the Manufacturer String
       // res = hid_get_manufacturer_string(m_handle, wstr, MAX_STR);
       // printf("Manufacturer String: %ls\n", wstr);

        // Read the Product String
        //res = hid_get_product_string(m_handle, wstr, MAX_STR);
        //printf("Product String: %ls\n", wstr);
        //size_t wcstombs(char* dest, const wchar_t* src, size_t max);

        //Set our self
        _vendorID = m_info->vendor_id;
        _vendorIDFriendlyName = FSUSBDevice::getFrendlyVendorNameFromID(_vendorID);
        _productID = m_info->product_id;
        _productIDFriendlyName = FSUSBDevice::getFrendlyProductNameFromID(_vendorID,_productID);
        _friendlyName = _vendorIDFriendlyName + " "+ _productIDFriendlyName;

        getGamepadFeatures(m_handle);
    }
    else
    {
        //errror
    }
}

std::string_view FSHIDAPIiJoystick::getDevicePath() const
{
    return m_devicePath;
}

hid_device * FSHIDAPIiJoystick::getHandel() const
{
    return m_handle;
}


FSHIDAPIiJoystick::~FSHIDAPIiJoystick()
{
    if(m_handle != nullptr)
    {
        hid_close(m_handle);
    }
     m_handle = nullptr;
}



