/**************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2013.

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

#pragma once
#include <vector>
#include <map>
#include "../Interfaces/IFSJoystickListener.h"
#include "../Interfaces/IFSJoystickInfo.h"
#include "../Interfaces/IFSDevice.h"
#include "../baseClasses/FSBaseDevice.h"
#include "../baseClasses/FSBaseEvent.h"
#include <stdlib.h>
#include <new>
#include <limits>
/** \mainpage FreeStick Cross Platform Joystick and Gamepad Library.
  *
  * Here is an example on how to use the library.<br>
  * Create a device manager and call init.<br>
  * Derive your class that is going to proceess joystick events from IFSJoystickListener and implmet you interface funtions<br>
  * then register your class with the Device Manager for the call back you are intrested in<br>
  * \code
    class JoystickEventHandler: public IFSJoystickListener
    {
       public:
           JoystickEventHandler();
           ~JoystickEventHandler();
           virtual void OnButtonDown(FSDeviceInputEvent event) {}
           virtual void OnButtonUp(FSDeviceInputEvent event) {}
           virtual void OnButtonUpdate(FSDeviceInputEvent event){ }
           virtual void OnStickMove(FSDeviceInputEvent event) { }
           virtual void OnStickMoveUpdate(FSDeviceInputEvent event){ }
           virtual void OnDisconnect(FSBaseEvent event){};
           virtual void OnConnect(FSBaseEvent event){};
    };

   void main()
   {
       JoystickEventHandler handler;
       FSUSBMacOSXJoystickDeviceManager deviceManager;
       deviceManager.init();
       deviceManager.ListenForJoystickConnection(&handler);
       deviceManager.ListenForJoystickDisconnections(&handler);
       deviceManager.ListenForAllJoysticksForEventType(FS_BUTTON_EVENT,*this);
       deviceManager.ListenForAllJoysticksForEventType(FS_AXIS_EVENT,*this);
       deviceManager.ListenForAllJoysticksForEventType(FS_TRIGGER_EVENT,*this);
   }
   \endcode
  */

namespace freestick
{

    /** \brief This is the base manager.
      *
      * This is the base manager with lots of verbose documentation.
      */

    class FSBaseManager
    {

    public:
        FSBaseManager();
        virtual ~FSBaseManager();
        /** \brief This is the base manager.
          *
          * This is the base manager with lots of verbose documentation.
          *
          * \param listener This is what a listener does.
          * \param joystickInfo This is what a joystickInfo does.
          */

        void ListenForJoystick(IFSJoystickListener & listener,unsigned int deviceID,FSDeviceInput input){};

        void UnListenForJoystick(IFSJoystickListener & listener ,unsigned int deviceID,FSDeviceInput input){};

        void ListenForAllJoysticks(IFSJoystickListener & listener){ ListenForJoystick(listener,0,AllInputs);}

        void UnListenForAllJoysticks(IFSJoystickListener & listener){ UnListenForJoystick(listener,0,AllInputs);}

        void ListenForJoystickConnection(IFSJoystickListener & listener);

        void ListenForJoystickDisconnections(IFSJoystickListener & listener);

        void UnListenForJoystickConnection(IFSJoystickListener & listener);

        void ListenForAllJoysticksForEventType(FreeStickEventType eventType,IFSJoystickListener & listener);

        void ListenForJoystickEvent(FreeStickEventType eventType,IFSJoystickListener & listener);

      // const std::vector<IFSJoystickInfo> & listOfConnectedJoysticks();
       virtual void init() ;
#pragma mark -Advance API
       const FSBaseDevice * getDevice(unsigned int deviceID);
       //these need to be protected



    private:
        std::multimap<FreeStickEventType,IFSJoystickListener * > _joystickDeviceListeners;
        std::map<unsigned int,std::multimap<FreeStickEventType,IFSJoystickListener * > > _joystickDeviceInputListeners;
        std::vector<IFSJoystickListener *> allJoystickListeners;
        std::map<unsigned int, FSBaseDevice * > deviceMap;
    protected:
        virtual void addDevice(FSBaseDevice * device);
        virtual void removeDevice(FSBaseDevice * device);
        virtual void inputOnDeviceChanged(FreeStickEventType eventType,FSEventAction eventAction,FSDeviceInput inputType,unsigned int deviceID,unsigned int deviceControlID,int newValue,int oldValue,signed long min, signed long max);
        virtual unsigned int getNextID();
        void updateEvent(FSBaseEvent & event);

    };
}
