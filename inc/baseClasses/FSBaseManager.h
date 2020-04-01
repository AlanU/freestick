/*******************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2013-2020.

This Code is free software; you can redistribute it and/or modify it under the
terms of the zlib/libpng License as published by the Free Software Foundation;
either version 2.1 of the License, or (at your option) any later version.  This
software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the
use of this software.

Permission is granted to anyone to use this software for any purpose, including
commercial applications, and to alter it and redistribute it freely, subject to
the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim
that you wrote the original software.  If you use this software in a product,
an acknowledgment in the product documentation would be appreciated but is not
required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
*******************************************************************************/

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
#include <limits>
#include <new>

/** \mainpage FreeStick Cross Platform Joystick and Gamepad Library.
 *
 * Here is an example on how to use the library.<br>
 * Create a device manager and call init.<br>
 * Derive your class that is going to proceess joystick events from IFSJoystickListener and implmet you interface funtions<br>
 * then register your class with the Device Manager for the call back you are intrested in<br>
 * \code
    #include "freestick.h"
    using namespace freestick;
    struct JoystickEventHandler:IFSJoystickListener
    {
        virtual~JoystickEventHandler() = default;
        JoystickEventHandler() = default;

        virtual void onButtonDown(const FSDeviceInputEvent& event){}
        virtual void onButtonUp(const FSDeviceInputEvent& event){}
        virtual void onStickMove(const FSDeviceInputEvent& event){}
        virtual void onDisconnect(const FSBaseEvent& event){}
        virtual void onConnect(const FSBaseEvent& event){}
    };

    void main()
    {
        JoystickEventHandler handler;
        FreeStickDeviceManager deviceManager;
        deviceManager.init();
        deviceManager.ListenForAllJoysticksForEventTypes(FS_JOYSTICK_ALL_EVENTS);
    }
 * \endcode
 */

namespace freestick
{
    /** \brief This is the base manager.
     *
     * This is the base manager with lots of verbose documentation.
     */

    class FSBaseManager
    {
        using joystickDeviceListenersItr = std::unordered_multimap<FreeStickEventType,std::pair<IFSJoystickListener*,bool> >::iterator;
        std::unordered_map<u32,std::multimap<FreeStickEventType,IFSJoystickListener* > > _joystickDeviceInputListeners;
        std::unordered_multimap<FreeStickEventType,std::pair<IFSJoystickListener*,bool> > _joystickDeviceListeners;
        std::vector<IFSJoystickListener*> allJoystickListeners;

        std::vector<std::pair<FreeStickEventType,IFSJoystickListener* > > _listenersToCleanUp;
        IFSDeviceIDCreator* _deviceIDCreator; //!< If not null called to get next decice id from.

    public:
        virtual void listenForAllJoysticksForEventTypes(
              const u32 eventFlags
            , IFSJoystickListener& listener);

        virtual void unListenForAllJoysticksForEventTypes(
              const u32 eventFlags
            , IFSJoystickListener& listener);

        float convertRawToNormalizedRanger(
              const f64 value
            , const minMaxNumber maxValue
            , const minMaxNumber minValue);

        virtual void init() ;
        virtual void init(IFSDeviceIDCreator* idCreator);

        virtual ~FSBaseManager();
        FSBaseManager();

#ifdef __APPLE__
#  pragma mark - Advance API -
#endif

        virtual const FSBaseDevice* getDevice(const idNumber deviceID);

    protected:
        std::unordered_map<u32,FSBaseDevice* > _deviceMap;

        virtual void addDevice(FSBaseDevice* device);
        virtual void removeDevice(FSBaseDevice* device);
        virtual void inputOnDeviceChanged(
            const FreeStickEventType eventType
          , const FSEventAction eventAction
          , const FSDeviceInput inputType
          , const idNumber deviceID
          , const idNumber deviceControlID
          , const s32 newValue
          , const s32 oldValue
          , const minMaxNumber min
          , const minMaxNumber max);
        virtual void inputOnDeviceChangedWithNormilzedValues(
            const FreeStickEventType eventType
          , const FSEventAction eventAction
          , const FSDeviceInput inputType
          , const idNumber deviceID
          , const idNumber deviceControlID
          , const f32 newValue
          , const f32 oldValue);
        virtual elementID getNextID();

        void listenForAllJoysticksForEventType(
            const FreeStickEventType eventType
          , IFSJoystickListener& listener);
        void unListenForAllJoysticksForEventType(
            const FreeStickEventType eventType
          , IFSJoystickListener& listener);
        void listenForJoystickEvent(
            const FreeStickEventType eventType
          , IFSJoystickListener& listener);
        void removeListenerForEventType(
            const FreeStickEventType eventType
          , IFSJoystickListener& listener);
        void updateEvent(FSBaseEvent& event);
    };
}
