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
#include <unordered_map>
#include "../Interfaces/IFSJoystickListener.h"
#include "../Interfaces/IFSJoystickInfo.h"
#include "../Interfaces/IFSDevice.h"
#include "../baseClasses/FSBaseDevice.h"
#include "../baseClasses/FSBaseEvent.h"
#include "../Interfaces/IFSDeviceIDCreator.h"
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
    #include "freestick.h"
    class JoystickEventHandler: public IFSJoystickListener
    {
       public:
           JoystickEventHandler();
           ~JoystickEventHandler();
           virtual void onButtonDown(FSDeviceInputEvent event) {}
           virtual void onButtonUp(FSDeviceInputEvent event) {}
           virtual void onStickMove(FSDeviceInputEvent event) { }
           virtual void onDisconnect(FSBaseEvent event){};
           virtual void onConnect(FSBaseEvent event){};
    };

    void main()
    {
       JoystickEventHandler handler;
       FreeStickDeviceManager deviceManager;
       deviceManager.init();
       deviceManager.ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT | FS_JOYSTICK_DISCONNECT_EVENT |  FS_BUTTON_EVENT | FS_AXIS_EVENT | FS_TRIGGER_EVENT , handler);
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

        virtual void ListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener);

        virtual void UnListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener);

      //  void ListenForJoystick(IFSJoystickListener & listener,unsigned int deviceID,FSDeviceInput input){};

       // void UnListenForJoystick(IFSJoystickListener & listener ,unsigned int deviceID,FSDeviceInput input){};


        inline float convertRawToNormalizedRanger(double value,MinMaxNumber maxValue,MinMaxNumber minValue);
      // const std::vector<IFSJoystickInfo> & listOfConnectedJoysticks();
       virtual void init() ;
       virtual void init(IFSDeviceIDCreator * idCreator);
#ifdef __APPLE__
#pragma mark -Advance API
#endif
       virtual const FSBaseDevice * getDevice(ElementID deviceID);
    private:
        std::unordered_multimap<FreeStickEventType,IFSJoystickListener * > _joystickDeviceListeners;
        typedef std::unordered_multimap<FreeStickEventType,IFSJoystickListener * >::iterator joystickDeviceListenersItr;

        std::unordered_map<unsigned int,std::multimap<FreeStickEventType,IFSJoystickListener * > > _joystickDeviceInputListeners;
        std::vector<IFSJoystickListener *> allJoystickListeners;
        IFSDeviceIDCreator * _devicIDCreator; //if not null called to get next decice id from
    protected:
        std::unordered_map<unsigned int, FSBaseDevice * > deviceMap;
        //void ListenForAllJoysticks(IFSJoystickListener & listener){ ListenForJoystick(listener,0,AllInputs);}
      //  void UnListenForAllJoysticks(IFSJoystickListener & listener){ UnListenForJoystick(listener,0,AllInputs);}
        void ListenForAllJoysticksForEventType(FreeStickEventType eventType,IFSJoystickListener & listener);
        void UnListenForAllJoysticksForEventType(FreeStickEventType eventType,IFSJoystickListener & listener);

        void ListenForJoystickEvent(FreeStickEventType eventType,IFSJoystickListener & listener);

        virtual void addDevice(FSBaseDevice * device);
        virtual void removeDevice(FSBaseDevice * device);
        virtual void inputOnDeviceChanged(FreeStickEventType eventType,FSEventAction eventAction,FSDeviceInput inputType,unsigned int deviceID,unsigned int deviceControlID,int newValue,int oldValue,MinMaxNumber min,MinMaxNumber max);
        virtual void inputOnDeviceChangedWithNormilzedValues(FreeStickEventType eventType, FSEventAction eventAction, FSDeviceInput inputType, unsigned int deviceID, unsigned int deviceControlID, float newValue, float oldValue);
        virtual ElementID getNextID();
        void updateEvent(FSBaseEvent & event);

    };
}
