/**************************************************************************
Created by Alan Uthoff on 10/13/2013
Copyright (C) 2013

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


#include "freestick.h"
#include "MacOSHUD.h"
#include "3rdParty/EELog/src/EELog.h"
#include <thread>
#include <chrono>
#include <iostream>

using namespace freestick;
class JoystickEventHandler: public IFSJoystickListener
   {
      public:
          JoystickEventHandler(){};
          ~JoystickEventHandler(){};
          virtual void onButtonDown(freestick::FSDeviceInputEvent event)
          {
              EE_INFO<<"ButtonDown "<<std::endl;
          }
          virtual void onButtonUp(freestick::FSDeviceInputEvent event)
          {
              EE_INFO<<"ButtonUp "<<std::endl;

          }
          virtual void onStickMove(freestick::FSDeviceInputEvent event)
          {
              EE_INFO<<"OnStickMove"<<std::endl;
          }
          virtual void onDisconnect(freestick::FSBaseEvent event)
          {
              EE_INFO<<"OnDisconnect"<<std::endl;

          }
          virtual void onConnect(freestick::FSBaseEvent event)
          {
              EE_INFO<<"OnConnect"<<std::endl;
          }
   };
int main(int argc, char *argv[])
{
    JoystickEventHandler handler;
    FreeStickDeviceManager deviceManager;

    deviceManager.init();
    deviceManager.ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                            FS_JOYSTICK_DISCONNECT_EVENT |
                                                            FS_BUTTON_EVENT | FS_AXIS_EVENT |
                                                            FS_TRIGGER_EVENT , handler);

#ifdef TARGET_OS_OSX
    MacOSHUD hud(true);
    hud.setUpForNSEvents();
#else
    char command = ' ';
     while(true)
     {
         command = std::cin.peek();
         if(tolower(command) == 'q')
         {
            hud.quitApp();
         }
         deviceManager.update();
     }
#endif

    return 0;
}
