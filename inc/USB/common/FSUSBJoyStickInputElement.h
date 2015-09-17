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

#pragma once
#include "FSUSBDevice.h"
#include <map>
#include "FSUSBDeviceManager.h"
#include <stack>
#include <queue>
namespace freestick
{


    class FSUSBJoyStickInputElement : public FSUSBDevice
    {
    private:
        /** \todo
         *typedef these private data members and other classes
         *so type of the elements can change easly if a given platform needs to
         */
        MinMaxNumber _elementMin;
        MinMaxNumber _elementMax;
        MinMaxNumber _oldValue;
        MinMaxNumber _value;
        MinMaxNumber _deadZoneMin;
        MinMaxNumber _deadZoneMax;
        bool _needsDeadZone;
        bool _calibrated;
        bool _intialized;
        FSUSBDeviceManager * _usbDeviceManager;
        time_t firstTime;
        std::queue<MinMaxNumber> _lastValueStack;
        bool _useLastValueStack;
        unsigned int _parentID;
        MinMaxNumber _buttonNumber;
    protected:
        void calibrate(PhysicalValueNumber currentValue, MinMaxNumber elementMin, MinMaxNumber elementMax );
        void EmptyQue(std::stack<FSUSBElementInfoMap> & infoMapsToReturn,unsigned int sizeToleft);
    public:
        //FSUSBJoyStickInputElement(const & FSUSBJoyStickInputElement copy){}
                 FSUSBJoyStickInputElement();
        FSUSBJoyStickInputElement(unsigned int id, unsigned int parentID, MinMaxNumber elementMin, MinMaxNumber elementMax, long venderID,long productID,FSUSBDeviceManager & _manager,PhysicalValueNumber currentValue,MinMaxNumber buttonNumber);
        void getMapping(int inputValue,std::stack<FSUSBElementInfoMap> & infoMapsToReturn) ;
        inline MinMaxNumber getValue() const {return _value;}
        void setValue(MinMaxNumber newValue);
        bool isValueInDeadZone(MinMaxNumber value);
        inline MinMaxNumber getMaxValue() const {return _elementMax;}
        inline MinMaxNumber getMinValue() const {return _elementMin;}
        inline MinMaxNumber getDeadZoneMin() const {return _deadZoneMin;}
        inline MinMaxNumber getDeadZoneMax() const {return _deadZoneMax;}
        inline MinMaxNumber getButtonNumber() const {return _buttonNumber;}
        void recalibrate(PhysicalValueNumber currentValue, MinMaxNumber elementMin, MinMaxNumber elementMax );

    };
}
