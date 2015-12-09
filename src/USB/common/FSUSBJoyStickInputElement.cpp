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

void FSUSBJoyStickInputElement::EmptyQue(std::stack<FSUSBElementInfoMap> & infoMapsToReturn,unsigned int sizeToleft)
{

    while(_lastValueStack.size() >sizeToleft)
    {
      MinMaxNumber stackValue = _lastValueStack.front();
      FSUSBElementInfoMap LastValueMap =  _usbDeviceManager->lookUpDeviceInputFromUSBID(_vendorID,_productID,getJoystickID(),_elementMin,_elementMax,stackValue);
      FSUSBElementInfoMap map = FSUSBElementInfoMap(LastValueMap.getMin(),LastValueMap.getMax(),LastValueMap.getDeviceInput(),FSInputRest);
      infoMapsToReturn.push(map);
      _lastValueStack.pop();
    }
}


//TODO change inputValue to a long for windows
void FSUSBJoyStickInputElement::getMapping(int inputValue ,std::stack<FSUSBElementInfoMap> & infoMapsToReturn)
{

    //asset(_usbDeviceManager != NULL);
   FSUSBElementInfoMap map = _usbDeviceManager->lookUpDeviceInputFromUSBID(_vendorID,_productID,getJoystickID(),_elementMin,_elementMax,inputValue);
   if(map.getDeviceInput() == LastValueUp)
   {
       EmptyQue(infoMapsToReturn,0);
   }
   else
   {

       if (_useLastValueStack && _lastValueStack.size() >2)
       {
            EmptyQue(infoMapsToReturn,(unsigned int)_lastValueStack.size()-1);
       }


      infoMapsToReturn.push(map);
      this->setValue(inputValue);

   }

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
    else if(_needsDeadZone && !_calibrated )
    {
        return false;
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

FSUSBJoyStickInputElement::FSUSBJoyStickInputElement(unsigned int id,  unsigned int parentID, MinMaxNumber elementMin, MinMaxNumber elementMax ,VenderIDType venderID,ProductIDType productID,FSUSBDeviceManager & _manager,PhysicalValueNumber currentValue,MinMaxNumber buttonNumber):FSUSBDevice(id,venderID,productID)
{
    _buttonNumber = buttonNumber;
     _elementMin = elementMin;
     _elementMax = elementMax;
     _oldValue = -1;
    _value = -2;
    _intialized =false;
    _usbDeviceManager = &_manager;

    _needsDeadZone = false;
    _calibrated =false;

    _useLastValueStack = false;

    _parentID = parentID;

   _useLastValueStack = _usbDeviceManager->doesElementHaveDeviceInputForValue(venderID,productID,id,LastValueUp);

    calibrate(currentValue,elementMin,elementMax);

    firstTime = time(NULL);
}

void FSUSBJoyStickInputElement::calibrate(PhysicalValueNumber currentValue, MinMaxNumber elementMin, MinMaxNumber elementMax )
{
    _needsDeadZone = false;
    _calibrated =false;

    _elementMin = elementMin;
    _elementMax = elementMax;
    FSDeviceInput deviceType = _usbDeviceManager->lookUpDeviceInputFromUSBID(_vendorID,_productID,getJoystickID(),_elementMin,_elementMax,currentValue).getDeviceInput();

    if(FS_isAxis(deviceType) )
   {
        if(! (currentValue == _elementMin || currentValue == _elementMax))
        {
           _deadZoneMax =  (currentValue < _elementMax) ?    currentValue :  _elementMax;
           _deadZoneMin =  (currentValue > _elementMin) ?    currentValue :  _elementMin;
        }
        else
        {
                _deadZoneMax =_elementMin+_elementMax/2;
                _deadZoneMin =_deadZoneMax;
        }
        if(_deadZoneMin > _deadZoneMax)
        {
           MinMaxNumber temp = _deadZoneMax;
           _deadZoneMax = _deadZoneMin ;
           _deadZoneMin = temp;
        }

        MinMaxNumber precent = static_cast<MinMaxNumber>(( (float)(_elementMax + std::abs(_elementMin) ) )*0.05f);

        _deadZoneMax= _elementMax < _deadZoneMax+precent ?  _deadZoneMax :_deadZoneMax + precent ;
        _deadZoneMin = _elementMin > _deadZoneMin-precent ? _deadZoneMin : _deadZoneMin - precent;

        _needsDeadZone = true;
   }
}

void FSUSBJoyStickInputElement::recalibrate(PhysicalValueNumber currentValue, MinMaxNumber elementMin, MinMaxNumber elementMax )
{
    calibrate(currentValue,elementMin,elementMax);
}
