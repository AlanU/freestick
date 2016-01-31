# FreeStick is a Cross Platform Joystick and Gamepad Library written in C++ 11 #

### Requirements ###
[Qmake](http://qt-project.org) - build system (The QT framework is NOT a requirement and is NOT used in this Lib)

C++ compiler

### Documentation ###
See the [wiki](https://bitbucket.org/freestick/freestick/wiki) and [doc](https://bitbucket.org/freestick/freestick/src/) folder in repo for more documentation.

### Getting started ###
The easies way to get started is to download [QT](http://qt-project.org/downloads) and open up the FreeStick.pro (to just build the lib) or FreeStickTestApp.pro (example program)
 
There is a NULL device if you wish to build and test the code out on an unsupported platform. 

### Notes ###
This code is in a alpha state and currently only works on MacOSX, Android, Windows (coming soon).

The future versions will support iOS, NDK Only Android ,and Linux.

We are looking for contributors. Contact AlanU for more information

###License###
FreeStick is licensed under the [Zlib license]( http://opensource.org/licenses/Zlib)
  
###Other Mirrors###
[GitHub mirror](https://github.com/AlanU/freestick)


###Example###
Create a device manager and call init.

Derive your class that is going to proceess joystick events from IFSJoystickListener and implement the interface funtions

Then register your class with the Device Manager for the call back you are intrested in

```c++
#include "freestick.h"
    class JoystickEventHandler: public IFSJoystickListener
    {
       public:
           JoystickEventHandler();
           ~JoystickEventHandler();
           virtual void onButtonDown(freestick::FSDeviceInputEvent event) {}
           virtual void onButtonUp(freestick::FSDeviceInputEvent event) {}
           virtual void onStickMove(freestick::FSDeviceInputEvent event) {}
           virtual void onDisconnect(freestick::FSBaseEvent event){};
           virtual void onConnect(freestick::FSBaseEvent event){};
    };

   void main()
   {
        JoystickEventHandler handler;
        FreeStickDeviceManager deviceManager;
        deviceManager.init();
        deviceManager.ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT | FS_JOYSTICK_DISCONNECT_EVENT |  FS_BUTTON_EVENT | FS_AXIS_EVENT | FS_TRIGGER_EVENT , handler);
   }
```