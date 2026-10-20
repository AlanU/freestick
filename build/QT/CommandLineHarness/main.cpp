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
#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>
#include <string>

using namespace freestick;
class JoystickEventHandler: public IFSJoystickListener
   {
      public:
          JoystickEventHandler(){};
          ~JoystickEventHandler(){};
          virtual void onButtonDown(freestick::FSDeviceInputEvent event)
          {
              std::cout<<"ButtonDown "<<std::endl;
          }
          virtual void onButtonUp(freestick::FSDeviceInputEvent event)
          {
              std::cout<<"ButtonUp "<<std::endl;

          }
          virtual void onStickMove(freestick::FSDeviceInputEvent event)
          {
              std::cout<<"OnStickMove"<<std::endl;
          }
          void onUnknownChanged(freestick::FSDeviceInputEvent event) override
          {
              std::cout << "OnUnknownChanged device=" << event.getDeviceID()
                        << " control=" << event.getControlID()
                        << " value=" << event.getNewInputValue() << std::endl;
          }
          virtual void onDisconnect(freestick::FSBaseEvent event)
          {
              std::cout<<"OnDisconnect"<<std::endl;

          }
          virtual void onConnect(freestick::FSBaseEvent event)
          {
              std::cout<<"OnConnect"<<std::endl;
          }
   };
int main(int argc, char *argv[])
{
    // Altered: allow a bounded initialization check without opening the Mac HUD.
    const bool smokeTest = argc == 2 && std::string(argv[1]) == "--smoke-test";
    JoystickEventHandler handler;
    FreeStickDeviceManager deviceManager;

    std::cout << "Starting FreeStick command-line harness" << std::endl;
    deviceManager.init();
    deviceManager.ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                            FS_JOYSTICK_DISCONNECT_EVENT |
                                                            FS_BUTTON_EVENT | FS_AXIS_EVENT |
                                                            FS_TRIGGER_EVENT | FS_UNKNOWN_EVENT, handler);

    if(smokeTest)
    {
        deviceManager.update();
        std::cout << "FreeStick initialization smoke test completed" << std::endl;
        return 0;
    }

#if defined(__APPLE__) && TARGET_OS_OSX
    MacOSHUD hud(true);
    hud.setUpForNSEvents();
#else
    // Altered: keep polling while input waits; quit on q or end of input.
    std::atomic<bool> running(true);
    std::thread inputThread([&running]() {
        char command;
        while(std::cin.get(command) && command != 'q' && command != 'Q') {}
        running = false;
    });
    while(running)
    {
        deviceManager.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    inputThread.join();
#endif

    return 0;
}
