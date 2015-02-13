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
#include "USB/common/FSUSBJoystick.h"
#include <time.h>
#include <cstdlib>

using namespace freestick;
FSUSBJoyStickInputElement::FSUSBJoyStickInputElement()
{
}

void FSUSBJoyStickInputElement::getMapping(int inputValue ,std::stack<FSUSBElementInfoMap> & infoMapsToReturn)
{

    //asset(_usbDeviceManager != NULL);
   FSUSBElementInfoMap map = _usbDeviceManager->lookUpDeviceInputFromUSBID(_vendorID,_productID,getJoystickID(),_elementMin,_elementMax,inputValue);
   if(map.getDeviceInput() == LastValueUp)
   {
       while(!_lastValueStack.empty())
       {
         MinMaxNumber stackValue = _lastValueStack.top();
         FSUSBElementInfoMap LastValueMap =  _usbDeviceManager->lookUpDeviceInputFromUSBID(_vendorID,_productID,getJoystickID(),_elementMin,_elementMax,stackValue);
         map = FSUSBElementInfoMap(LastValueMap.getMin(),LastValueMap.getMax(),LastValueMap.getDeviceInput(),FSInputRest);
         infoMapsToReturn.push(map);
         _lastValueStack.pop();
       }
   }
   else
   {
      infoMapsToReturn.push(map);
   }
   this->setValue(inputValue);

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
    double diffranceInTime = difftime(time(NULL),firstTime);

    if(_needsDeadZone && !_calibrated  && (diffranceInTime <1.5))
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

    if( diffranceInTime>0.3 && (!_calibrated && _needsDeadZone))
    {
        
        _calibrated = true;

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
    if(_useLastValueStack ) {_lastValueStack.push(_value);}
}

FSUSBJoyStickInputElement::FSUSBJoyStickInputElement(unsigned int id, MinMaxNumber elementMin, MinMaxNumber elementMax ,long venderID,long productID,FSUSBDeviceManager & _manager,PhysicalValueNumber currentValue):FSUSBDevice(id,venderID,productID)
{
    
     _elementMin = elementMin;
     _elementMax = elementMax;
     _oldValue = -1;
    _value = -2;
    _intialized =false;
    _usbDeviceManager = &_manager;

    _needsDeadZone = false;
    _calibrated =false;

    FSDeviceInput deviceType = _usbDeviceManager->lookUpDeviceInputFromUSBID(venderID,productID,id,_elementMin,_elementMax,currentValue).getDeviceInput();
    _useLastValueStack = false;

   if(deviceType == LastValueUp)
   {
       _useLastValueStack = true;
   }
    //TODO calibrated needs to be called over a time interval not number of times
    if(FS_isAxis(deviceType) )
    {
        _deadZoneMax =  (currentValue < _elementMax) ?    currentValue :  _elementMax;
        _deadZoneMin =  (currentValue > _elementMin) ?    currentValue :  _elementMin;
        
        if(_deadZoneMin > _deadZoneMax)
        {
            MinMaxNumber temp = _deadZoneMax;
            _deadZoneMax = _deadZoneMin ;
            _deadZoneMin = temp;
        }
        
        MinMaxNumber precent =( (float)(_elementMax + abs(_elementMin) ) )*0.05f;
        
        _deadZoneMax= _elementMax < _deadZoneMax+precent ?  _deadZoneMax :_deadZoneMax + precent ;
        _deadZoneMin = _elementMin > _deadZoneMin-precent ? _deadZoneMin : _deadZoneMin - precent;
        
        _needsDeadZone = true;
    }
    firstTime = time(NULL);



}
