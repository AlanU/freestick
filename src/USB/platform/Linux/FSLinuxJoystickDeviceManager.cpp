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
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <string>

using namespace freestick;
FSLinuxJoystickDeviceManager::FSLinuxJoystickDeviceManager()
{
    updateConnectJoysticks();
}

void FSLinuxJoystickDeviceManager::update()
{

}

void FSLinuxJoystickDeviceManager::updateConnectJoysticks()
{
    int joy_fd = 0;
    //keep a set of all open /dev/js joystick
    //check known joysticks to see if they can be opened or found in the list
    //if not then they have been disconnected
    //Read all direcories in /dev and look for jsx where x is number using readdir also check to see if its a directory
    //skip . and ..
    //if they are not in the list then they are new connected joysticks

    DIR * dirPtr = nullptr;
    struct dirent * entryDir = nullptr;
    struct stat entryDirStat ;

    if((dirPtr = opendir("/dev/input")) == nullptr)
    {
        return ;
    }

    //TODO see if there is a more efficent way to read all the directories
    //TODO move over to using the evdev interface instead of the old way
    //https://wiki.archlinux.org/index.php/Gamepad
    while((entryDir = readdir(dirPtr)))
    {
        lstat(entryDir->d_name,&entryDirStat);
        std::size_t nameLength = std::char_traits<char>::length(entryDir->d_name);
        if(S_ISDIR(entryDirStat.st_mode) && nameLength >= 3 &&
                entryDir->d_name[0] == 'j' && entryDir->d_name[1] =='s' &&  isdigit(entryDir->d_name[2]) )
        {
            std::cout<<entryDir->d_name<<std::endl;
            if(_linuxDeviceIDMap.find(entryDir->d_name) == _linuxDeviceIDMap.end())
            {
                 IDNumber id = getNextID();
                _linuxDeviceIDMap[entryDir->d_name] = id;
                //TODO create a FSLinuxJoystick class
                FSUSBJoystick * newJoystick =  new FSUSBJoystick(id,0 /*number of buttons*/,0 /*number of analog sticks*/ ,0 /*number of dpads*/,false /*does it support force feedback*/,0/* venderID*/,0/*productID*/ );
                addDevice(newJoystick);
            }
        }
    }



    closedir(dirPtr);
   /* if(joy_fd = open( "/dev/js0" , O_RDONLY)) == -1 )
    {
        printf( "Couldn't open joystick\n" );
        return -1;
    }*/

}

void FSLinuxJoystickDeviceManager::updateJoysticks()
{

}
