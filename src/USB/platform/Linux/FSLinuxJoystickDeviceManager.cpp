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
#include <set>
#include <libusb.h>
using namespace freestick;
int r = -1;
int verbose = 0;
ssize_t cnt;
libusb_device **devs;
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
                if (rc >=0 && !(ev.type == EV_SYN && ev.code == SYN_REPORT))
                    printf("Event: %s %s %d\n",
                           libevdev_event_type_get_name(ev.type),
                           libevdev_event_code_get_name(ev.type, ev.code),
                           ev.value);

                FSLinuxJoystick::HIDMapping hidUsage = FSLinuxJoystick::getHIDUsageAndPage(ev.type,ev.code);
                auto element = (FSUSBJoyStickInputElement*)controller->findInputElement( FSUSBJoystickDeviceManager::createIdForElement(static_cast<uint32_t>(hidUsage.usage),static_cast<uint32_t>(hidUsage.usage_page)));
                updateEvents(controller->getJoystickID(),element, ev.value);
            } while (rc != -EAGAIN);
         }
        //close(fd);
     }
}

void FSLinuxJoystickDeviceManager::updateConnectJoysticks()
{
    libevdev * m_evdevHandel = nullptr;
    std::set<std::string> connecteContorllers (_linuxMapKeys);
    std::string path = "/dev/input/";
    for (const auto & entry : std::filesystem::directory_iterator(path)) {

        int rc = -1;
        int fd = 0;

        if(_linuxDeviceIDMap.find(entry.path()) == _linuxDeviceIDMap.end())
        {
            int fd = open(entry.path().c_str(), O_RDONLY|O_NONBLOCK);
            rc = libevdev_new_from_fd(fd, &m_evdevHandel);
        }
        if (rc >= 0) {
            vendorIDType vendorID = libevdev_get_id_vendor(m_evdevHandel);
            productIDType productID = libevdev_get_id_product(m_evdevHandel);
            std::string deviceName =  libevdev_get_name(m_evdevHandel);
            /*printf("Input device name: \"%s\"\n", libevdev_get_name(m_evdevHandel));
            printf("Input device ID: bus %#x vendor %#x product %#x\n",
                   libevdev_get_id_bustype(m_evdevHandel),
                   libevdev_get_id_vendor(m_evdevHandel),
                   libevdev_get_id_product(m_evdevHandel));*/
            if (!libevdev_has_event_type(m_evdevHandel, EV_ABS))
                {
                printf("This device does not look like a gamepad\n");
                exit(1);
            }
            if(_linuxDeviceIDMap.find(entry.path()) == _linuxDeviceIDMap.end())
            {
                idNumber id = getNextID();
                _linuxDeviceIDMap[entry.path()] = id;
                _linuxMapKeys.insert(entry.path());
                FSUSBJoystick * newJoystick =  new FSLinuxJoystick(id,
                                                                   m_evdevHandel,
                                                                   fd,
                                                                   entry.path(),
                                                                   vendorID,
                                                                 productID,*this);
                addDevice(newJoystick);
            }
            else {
                connecteContorllers.erase(entry.path());
            }

        }else{
            m_evdevHandel = nullptr;
          // close(fd); //This conflicts with file loop TODO figure this out
        }
    }
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
