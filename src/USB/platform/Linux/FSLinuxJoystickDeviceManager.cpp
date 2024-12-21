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
#include "USB/platform/Linux/FSLinuxJoystickDeviceManager.h"
#include "USB/common/FSUSBJoystick.h"
#include "USB/platform/Linux/FSLinuxJoystick.h"
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <filesystem>
#include <regex>
#include <set>
#include <dirent.h>

using namespace freestick;
int r = -1;
int verbose = 0;
ssize_t cnt;
FSLinuxJoystickDeviceManager::FSLinuxJoystickDeviceManager()
{
   // r = libusb_init_context(/*ctx=*/NULL, /*options=*/NULL, /*num_options=*/0);
   // r = libusb_init(nullptr);
}


void FSLinuxJoystickDeviceManager::update()
{
     updateConnectJoysticks();
    int rc = -EAGAIN;
    for(const std::string & event : _linuxMapKeys) //TODO make this more effient
    {
        FSLinuxJoystick * controller = (FSLinuxJoystick *)getDevice(_linuxDeviceIDMap[event]);
        int rc = 1;
        if(controller &&  controller->getHandel() != nullptr)
        {
             /* int fd = open(event.c_str(), O_RDONLY|O_NONBLOCK);
            rc = libevdev_new_from_fd(fd, &m_evdevHandel);
            if (rc < 0) {
                //fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
                continue;
            }*/
            do {
                struct input_event ev;
                rc = libevdev_next_event(controller->getHandel(), LIBEVDEV_READ_FLAG_NORMAL, &ev);
                if (rc >=0 && !(ev.type == EV_SYN && ev.code == SYN_REPORT) )
                    if( ev.code != ABS_Z)   {
                printf("Event: %s %s %d\n",
                           libevdev_event_type_get_name(ev.type),
                           libevdev_event_code_get_name(ev.type, ev.code),
                           ev.value);
                        // If the event is for the dpad horizontal axis (ABS_HAT0X)
                        if (ev.code == ABS_HAT0X) {
                            if (ev.value == -1) {
                                printf("Dpad Left\n");
                            } else if (ev.value == 1) {
                                printf("Dpad Right\n");
                            } else if (ev.value == 0) {
                                printf("Dpad Centered\n");
                            }
                        }
                    }

                FSLinuxJoystick::HIDMapping hidUsage = FSLinuxJoystick::getHIDUsageAndPage(ev.type,ev.code);
                int32_t fsValue = controller->getDpadDeviceInput(ev.type,ev.code,ev.value);//this will return back the code if its not a dpad
                auto element = (FSUSBJoyStickInputElement*)controller->findInputElement( FSUSBJoystickDeviceManager::createIdForElement(static_cast<uint32_t>(hidUsage.usage),static_cast<uint32_t>(hidUsage.usage_page)));
                updateEvents(controller->getJoystickID(),element, fsValue);
            } while (rc != -EAGAIN);
         }
        //close(fd);
     }
}

void FSLinuxJoystickDeviceManager::updateConnectJoysticks()
{
    libevdev * m_evdevHandel = nullptr;
    std::set<std::string> connectedControllers (_linuxMapKeys);

    std::string path = "/dev/input/";
    DIR* dir = opendir(path.c_str());
    if (!dir) {
        perror("Failed to open directory");
        return;
    }

        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type != DT_CHR) {
                continue; // Skip non-regular files
            }

            // Validate that the file name matches the expected pattern (e.g., event*)
            std::string deviceName = entry->d_name;
            if (!std::regex_match(deviceName, std::regex("event[0-9]+"))) {
                continue; // Skip non-evdev files
            }


            std::string fullPath = path + entry->d_name;
            int fd = open(fullPath.c_str(), O_RDONLY | O_NONBLOCK);
            if (fd < 0) {
               /* if (errno == EACCES) {
                    std::cerr << "Permission denied for device: " << fullPath << "\n";
                } else {
                    perror(("Failed to open device: " + fullPath).c_str());
                }*/
                continue; // Skip to the next file
            }


            int rc = libevdev_new_from_fd(fd, &m_evdevHandel);
            if (rc < 0) {
                perror("Failed to initialize libevdev");
                close(fd);
                m_evdevHandel = nullptr;
                continue; // Skip to the next file
            }

            if (libevdev_has_event_type(m_evdevHandel, EV_ABS)) {
                if (_linuxDeviceIDMap.find(entry->d_name) == _linuxDeviceIDMap.end()) {
                    idNumber id = getNextID();
                    _linuxDeviceIDMap[entry->d_name] = id;
                    _linuxMapKeys.insert(entry->d_name);
                    std::cout << " Found controller "<<entry->d_name<<std::endl;
                    std::cout << " createing controller "<<entry->d_name<<std::endl;
                    vendorIDType vendorID = libevdev_get_id_vendor(m_evdevHandel);
                    productIDType productID = libevdev_get_id_product(m_evdevHandel);
                    libevdev_free(m_evdevHandel);
                    m_evdevHandel = nullptr;
                    close(fd);
                    auto* newJoystick = new FSLinuxJoystick(id, fullPath,
                                                          vendorID,
                                                          productID,
                                                          *this);
                    std::cout << "addDevice "<<entry->d_name<<std::endl;

                    addDevice(newJoystick);
                } else {
                    connectedControllers.erase(entry->d_name);
                }
            } else {
                std::cout << "This device does not look like a gamepad\n";
            }
            if(m_evdevHandel != nullptr)
            {
                libevdev_free(m_evdevHandel);
                m_evdevHandel = nullptr;
                close(fd);
            }
        }

        closedir(dir);

    /*if(connecteContorllers.size() != 0)
    {
        for(const std::string & controller : connecteContorllers)
        {
            const FSBaseDevice *  deviceToRemove = getDevice(_linuxDeviceIDMap[controller]);
            if(deviceToRemove != nullptr)
            {
                _linuxDeviceIDMap.erase(controller);
                _linuxMapKeys.erase(controller);
                removeDevice((FSBaseDevice *)deviceToRemove); //frees the memory
            }
        }
        m_evdevHandel  = nullptr;
    }*/
 }


void FSLinuxJoystickDeviceManager::updateJoysticks()
{

}
