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

#include "baseClasses/FSBaseManager.h"
#include <utility>      // std::pair
#include "baseClasses/FSBaseEvent.h"
#include "common/FSDeviceInputEvent.h"
#include "common/FreeStickLog.h"
#include <ctime>
using namespace freestick;

FSBaseManager::FSBaseManager()
{
    _devicIDCreator = nullptr;
}

void FSBaseManager::init( )
{
    //Init joystick here

    deviceMap.clear();
}


void FSBaseManager::init(IFSDeviceIDCreator * idCreator)
{
    _devicIDCreator = idCreator;
    init();
}


FSBaseManager::~FSBaseManager()
{
    if( deviceMap.size() !=0)
    {
        for( std::unordered_map<unsigned int, FSBaseDevice * >::iterator itr = deviceMap.begin() ; itr != deviceMap.end(); ++itr)
        {
            delete itr->second;
        }
    }
    deviceMap.clear();
    _joystickDeviceListeners.clear();
    allJoystickListeners.clear();
    _listenersToCleanUp.clear();

}

const FSBaseDevice * FSBaseManager::getDevice(elementID deviceID)
{
    if(deviceMap.find(deviceID) != deviceMap.end())
        return deviceMap[deviceID];
    else
        return nullptr;
}

void  FSBaseManager::ListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener)
{
    if(eventFlags & FS_JOYSTICK_CONNECTED_EVENT)
    {
        if(!deviceMap.empty())
        {
            std::unordered_map<unsigned int, FSBaseDevice * >::iterator itr;
            for(itr = deviceMap.begin(); itr != deviceMap.end(); ++itr)
            {
                FSBaseDevice * device = itr->second;
                FSBaseEvent newConnectEvent(FS_JOYSTICK_CONNECTED_EVENT,FSInputChanged,std::time(0),device->getJoystickID());
                
                listener.onConnect(newConnectEvent);
            }
            
        }
        ListenForAllJoysticksForEventType(FS_JOYSTICK_CONNECTED_EVENT,listener);
    }
    if(eventFlags & FS_JOYSTICK_DISCONNECT_EVENT)
    {
        ListenForAllJoysticksForEventType(FS_JOYSTICK_DISCONNECT_EVENT,listener);
    }
    if(eventFlags & FS_BUTTON_EVENT)
    {
        ListenForAllJoysticksForEventType(FS_BUTTON_EVENT,listener);
    }
    if(eventFlags & FS_AXIS_EVENT)
    {
        ListenForAllJoysticksForEventType(FS_AXIS_EVENT,listener);
    }
    if(eventFlags & FS_TRIGGER_EVENT)
    {
        ListenForAllJoysticksForEventType(FS_TRIGGER_EVENT,listener);
    }
    if(eventFlags & FS_UNKNOWN_EVENT)
    {
        ListenForAllJoysticksForEventType(FS_UNKNOWN_EVENT,listener);
    }

}
void  FSBaseManager::UnListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener)
{
    if(eventFlags & FS_JOYSTICK_CONNECTED_EVENT)
    {
        UnListenForAllJoysticksForEventType(FS_JOYSTICK_CONNECTED_EVENT ,listener);
    }
    if(eventFlags & FS_JOYSTICK_DISCONNECT_EVENT)
    {
        UnListenForAllJoysticksForEventType(FS_JOYSTICK_DISCONNECT_EVENT,listener);
    }
    if(eventFlags & FS_BUTTON_EVENT)
    {
        UnListenForAllJoysticksForEventType(FS_BUTTON_EVENT,listener);
    }
    if(eventFlags & FS_AXIS_EVENT)
    {
        UnListenForAllJoysticksForEventType(FS_AXIS_EVENT,listener);
    }
    if(eventFlags & FS_UNKNOWN_EVENT)
    {
        UnListenForAllJoysticksForEventType(FS_UNKNOWN_EVENT,listener);
    }
    if(eventFlags & FS_TRIGGER_EVENT)
    {
        UnListenForAllJoysticksForEventType(FS_TRIGGER_EVENT,listener);
    }
}



/*void FSBaseManager::ListenForJoystickDisconnections(IFSJoystickListener & listener)
{
    ListenForAllJoysticksForEventType(FS_JOYSTICK_DISCONNECT_EVENT,listener);
}

void FSBaseManager::UnListenForJoystickConnection(IFSJoystickListener & listener)
{

}

void FSBaseManager::ListenForJoystickConnection(IFSJoystickListener & listener)
{
    ListenForAllJoysticksForEventType(FS_JOYSTICK_CONNECTED_EVENT,listener);
}*/
void FSBaseManager::UnListenForAllJoysticksForEventType(FreeStickEventType eventType,IFSJoystickListener & listener)
{
    std::pair<joystickDeviceListenersItr,joystickDeviceListenersItr> rangeOfListeners;
   rangeOfListeners =  _joystickDeviceListeners.equal_range(eventType);
    joystickDeviceListenersItr itr = rangeOfListeners.first;
    while(itr != rangeOfListeners.second )
    {
        if(itr->second.first == (&listener))
        {
            itr->second.second = false;
            ++itr;
            _listenersToCleanUp.push_back(std::make_pair(eventType,&listener));
        }
        else
        {
            ++itr;
        }
    }
  
}


void FSBaseManager::RemoveListenerForEventType(FreeStickEventType eventType,IFSJoystickListener & listener)
{
    std::pair<joystickDeviceListenersItr,joystickDeviceListenersItr> rangeOfListeners;
   rangeOfListeners =  _joystickDeviceListeners.equal_range(eventType);
    joystickDeviceListenersItr itr = rangeOfListeners.first;
    while(itr != rangeOfListeners.second )
    {
        if(itr->second.first == (&listener))
        {
            joystickDeviceListenersItr toErase = itr;
            ++itr;
            _joystickDeviceListeners.erase(toErase);
        }
        else
        {
            ++itr;
        }
    }

}

void FSBaseManager::ListenForAllJoysticksForEventType(FreeStickEventType eventType,IFSJoystickListener & listener)
{
    std::pair<IFSJoystickListener *,bool> foo(&listener,true);
    _joystickDeviceListeners.insert(std::pair<FreeStickEventType,std::pair<IFSJoystickListener *,bool> >(eventType,foo));

}
/*const std::vector<IFSJoystickInfo> & FSBaseManager::listOfConnectedJoysticks()
 {
     std::vector<IFSJoystickInfo> * temp = new std::vector<IFSJoystickInfo>;
     return *temp;
 }*/
//add event

void FSBaseManager::updateEvent(FSBaseEvent & event)
{
    std::pair<std::unordered_multimap<FreeStickEventType,std::pair<IFSJoystickListener *,bool> >::iterator, std::unordered_multimap<FreeStickEventType,std::pair<IFSJoystickListener *,bool> >::iterator> rangedItr;
    rangedItr = _joystickDeviceListeners.equal_range(event.getEventType());
    IFSJoystickListener * ListenerToCall = nullptr;
    while (rangedItr.first != rangedItr.second)
    {
        if(rangedItr.first->second.second)
        {
            ListenerToCall = rangedItr.first->second.first;
            switch (event.getEventType())
            {
            case FS_JOYSTICK_CONNECTED_EVENT:
                ListenerToCall->onConnect(event);
                break;
            case FS_JOYSTICK_DISCONNECT_EVENT:
                ListenerToCall->onDisconnect(event);
                break;
            case FS_BUTTON_EVENT:
                if (event.getEventAction() == FSInputRest)
                    ListenerToCall->onButtonUp(*static_cast<FSDeviceInputEvent *>(&event));
                else
                    ListenerToCall->onButtonDown(*static_cast<FSDeviceInputEvent *>(&event));
                break;
            case FS_TRIGGER_EVENT:
            case FS_AXIS_EVENT:
                ListenerToCall->onStickMove(*static_cast<FSDeviceInputEvent *>(&event));
                break;
            case FS_UNKNOWN_EVENT:
                 ListenerToCall->onUnknownChanged(*(FSDeviceInputEvent *)&event);
                break;
            default:
                break;
            }
        }
        ++rangedItr.first;
    }


    auto rangedItrDevice = _joystickDeviceInputListeners[(static_cast<FSDeviceInputEvent *>(&event))->getDeviceID()].equal_range(event.getEventType());
    while (rangedItrDevice.first != rangedItrDevice.second)
    {
        ListenerToCall = rangedItrDevice.first->second;
        switch (event.getEventType())
        {
        case FS_BUTTON_EVENT:
            if ( event.getEventAction() == FSInputPressed )
                ListenerToCall->onButtonDown(*(FSDeviceInputEvent *)&event);
            else
                ListenerToCall->onButtonUp(*(FSDeviceInputEvent *)&event);
            break;
        case FS_TRIGGER_EVENT:
        case FS_AXIS_EVENT:
            ListenerToCall->onStickMove(*(FSDeviceInputEvent *)&event);
            break;
        case FS_UNKNOWN_EVENT:
             ListenerToCall->onUnknownChanged(*(FSDeviceInputEvent *)&event);
            break;
        default:
            break;
        }
        ++rangedItrDevice.first;
    }

    while (!_listenersToCleanUp.empty())
    {
        std::pair<FreeStickEventType,IFSJoystickListener * >  * toDelete = & _listenersToCleanUp[0];

        if(toDelete != nullptr && toDelete->second != nullptr)
        {
            RemoveListenerForEventType(toDelete->first,*(toDelete->second));
        }
       _listenersToCleanUp.erase(_listenersToCleanUp.begin());
    }

}

float FSBaseManager::convertRawToNormalizedRanger(double value,minMaxNumber maxValue,minMaxNumber minValue)
{

    double joystickRange = (double)maxValue - (double)minValue;

    if(joystickRange == 0)
        return -1;
    
    double libRange = 2;
    
    float newNormilzedValue = static_cast<float>( ( (( value - (double) minValue) * libRange)/joystickRange ) + -1.0 );
    return  newNormilzedValue;
    
}
void FSBaseManager::inputOnDeviceChangedWithNormilzedValues(FreeStickEventType eventType,
                                         FSEventAction eventAction,
                                         FSDeviceInput inputType,
                                         idNumber deviceID,
                                         idNumber deviceControlID,
                                         float newValue,
                                         float oldValue)
{
    FSDeviceInputEvent newInputEvent(eventType,eventAction,std::time(0),deviceID,deviceControlID,
                                     oldValue,
                                     newValue,
                                     inputType);
    updateEvent(newInputEvent);
}


void FSBaseManager::inputOnDeviceChanged(FreeStickEventType eventType,FSEventAction eventAction,FSDeviceInput inputType,idNumber deviceID, idNumber deviceControlID,int newValue,int oldValue,minMaxNumber min, minMaxNumber max)
{
    inputOnDeviceChangedWithNormilzedValues(eventType,eventAction,inputType,deviceID,deviceControlID, convertRawToNormalizedRanger(newValue,max,min), convertRawToNormalizedRanger(oldValue,max,min));
}

void FSBaseManager::addDevice(FSBaseDevice * device)
{
    deviceMap[device->getJoystickID()] = device;
    FSBaseEvent newConnectEvent(FS_JOYSTICK_CONNECTED_EVENT,FSInputChanged,std::time(0),device->getJoystickID());
    updateEvent(newConnectEvent);
    EE_DEBUG<<"added device with ID "<<device->getJoystickID()<<std::endl;
    EE_DEBUG<<"device map "<<deviceMap.size()<<std::endl;
}

//Note deletes device
void FSBaseManager::removeDevice(FSBaseDevice * device)
{
    if(device)
    {
        deviceMap.erase(device->getJoystickID());
        FSBaseEvent newConnectEvent(FS_JOYSTICK_DISCONNECT_EVENT,FSInputChanged,std::time(0),device->getJoystickID());
        updateEvent(newConnectEvent);
        EE_DEBUG<<"removed device with ID "<<device->getJoystickID()<<std::endl;
        delete device;
        device = NULL;
        EE_DEBUG<<"device map "<<deviceMap.size()<<std::endl;
    }

}

elementID FSBaseManager::getNextID()
{
    static unsigned int ID = 1;//0 is reserved for errors
    if(_devicIDCreator != NULL)
        return _devicIDCreator->getNextID();
    else
        return (ID++);

}

