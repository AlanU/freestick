/**************************************************************************
Created by Alan Uthoff on 11/12/2013
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

#include "USB/common/FSUSBJoyStickInputElement.h"
#include <time.h>
using namespace freestick;
FSUSBJoyStickInputElement::FSUSBJoyStickInputElement()
{
}

FSUSBElementInfoMap FSUSBJoyStickInputElement::getMapping(int inputValue)
{
    //asset(_usbDeviceManager != NULL);
   FSUSBElementInfoMap map = _usbDeviceManager->lookUpDeviceInputFromUSBID(_vendorID,_productID,getJoystickID(),_elementMin,_elementMax,inputValue);
   if(map.getDeviceInput() == LastValueUp)
   {
         FSUSBElementInfoMap LastValueMap =  _usbDeviceManager->lookUpDeviceInputFromUSBID(_vendorID,_productID,getJoystickID(),_elementMin,_elementMax,_value);
         map = FSUSBElementInfoMap(LastValueMap.getMin(),LastValueMap.getMax(),LastValueMap.getDeviceInput(),FSInputRest);
   }
   this->setValue(inputValue);
   return map;
}

bool FSUSBJoyStickInputElement::isValueInDeadZone(MinMaxNumber value)
{
    if(_calibrated && _needsDeadZone)
    {
        if (value <= _deadZoneMax && value >= _deadZoneMin)
        {
            return false;
        }
    }
    return true;
}

void FSUSBJoyStickInputElement::setValue(MinMaxNumber newValue)
{
    static time_t firstTime = time(NULL);


    if(_needsDeadZone && !_calibrated)
    {
        if(_intialized == false)
        {
            _deadZoneMax = newValue;
            _deadZoneMin = newValue;
        }
        else
        {
            if(_deadZoneMax < newValue)
            {
                _deadZoneMax = newValue;
            }
            if(_deadZoneMin > newValue)
            {
                _deadZoneMin = newValue;
            }
        }
    }

    double diffranceInTime = difftime(time(NULL),firstTime);
    if( diffranceInTime>0.3 && (!_calibrated && _needsDeadZone))
    {
        if(_deadZoneMax != _deadZoneMin && (diffranceInTime <1.5))
        {
            _deadZoneMax++;
            _deadZoneMin--;
        }
        else
        {
            _needsDeadZone = false;
        }
        _calibrated = true;

    }
    if(_calibrated && _needsDeadZone)
    {
        if (newValue <= _deadZoneMax && newValue >= _deadZoneMin)
        {
            newValue = (_elementMax/2);
        }
    }
    if (_intialized == false)
    {
        _oldValue = newValue;
        _value = newValue;
        _intialized = true;
    }
    if (newValue != _value )
    {
        _oldValue = _value;
        _value = newValue;
    }
}

FSUSBJoyStickInputElement::FSUSBJoyStickInputElement(unsigned int id, MinMaxNumber elementMin, MinMaxNumber elementMax ,long venderID,
                                                     long productID,FSUSBDeviceManager & _manager):FSUSBDevice(id,venderID,productID)
{
     _elementMin = elementMin;
     _elementMax = elementMax;
     _oldValue = -1;
    _value = -2;
    _intialized =false;
    _usbDeviceManager = &_manager;

    _needsDeadZone = false;
    _calibrated =false;
    //TODO calibrated needs to be called over a time interval not number of times
    if(!((_elementMax - _elementMin == 1) || ( _elementMax - _elementMin == 0)) )
        _needsDeadZone = true;
}
