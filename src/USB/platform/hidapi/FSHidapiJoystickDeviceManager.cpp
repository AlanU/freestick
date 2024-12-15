/**************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2016.

This Code is free software; you can redistribute it and/or
modify it under the terms of the zlib/libpng License as published
by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
**************************************************************************/
#include "USB/platform/hidapi/FSHidapiJoystickDeviceManager.h"
#include "USB/common/FSUSBJoystick.h"
#include "USB/platform/hidapi/FSHidapiJoystick.h"
#include <iostream>
#include <set>


#include "hidapi.h"
#include <string.h>

constexpr unsigned short Page_Generic_Desktop = 0x01;
constexpr unsigned short Usage_GamePad= 0x04;
constexpr unsigned short Usage_Joystick = 0x05;
using namespace freestick;
std::unordered_map<std::string_view,idNumber> m_connectDevices;

FSHIDAPIJoystickDeviceManager::FSHIDAPIJoystickDeviceManager()
{
 int res = hid_init();
}


void FSHIDAPIJoystickDeviceManager::update()
{
     updateConnectJoysticks();
}


void FSHIDAPIJoystickDeviceManager::updateConnectJoysticks()
{
    hid_device *handle = nullptr;

    // Initialize the hidapi library


    const char *path_to_open = NULL;

    /* register_global_error: global error is reset by hid_enumerate/hid_init */
    struct hid_device_info* devices = hid_enumerate(0x0, 0x0);
    if (devices == NULL) {
        /* register_global_error: global error is already set by hid_enumerate */
        return;
    }

    std::vector<std::string_view> m_newConnectControllers;
       //create a data member copy of connect contorllers
    std::unordered_map<std::string_view,idNumber> currentlyConnected(m_connectDevices) ;


    struct hid_device_info* currentDevice = devices;

    while (currentDevice) {
        // Call the lambda on each device

        if (currentDevice->usage_page == Page_Generic_Desktop &&
            (currentDevice->usage == Usage_GamePad || currentDevice->usage == Usage_Joystick ))
        {
            //Device Found
            if(m_connectDevices.find(currentDevice->path) != m_connectDevices.end() )
            {
                currentlyConnected.erase(currentDevice->path);
            }
            else
            {
                m_newConnectControllers.push_back(currentDevice->path);
            }
            path_to_open = currentDevice->path;
        }

    currentDevice = currentDevice->next;
    }


    for(auto path : m_newConnectControllers)
    {
        FSHIDAPIiJoystick * temp = new FSHIDAPIiJoystick(path,this->getNextID());
        m_connectDevices[temp->getDevicePath()] = temp->getJoystickID();
        //temp->Init(*this);
        this->addDevice(temp);
    }

    for(auto & it:currentlyConnected)
    {
        const FSHIDAPIiJoystick *  deviceToDelete =  static_cast<const FSHIDAPIiJoystick*>(getDevice(it.second));
        m_connectDevices.erase(deviceToDelete->getDevicePath());
        removeDevice((FSBaseDevice *)(deviceToDelete));

        //erase joystick
    }

    hid_free_enumeration(devices);

 }



void FSHIDAPIJoystickDeviceManager::updateJoysticks()
{


    hid_exit();
}
