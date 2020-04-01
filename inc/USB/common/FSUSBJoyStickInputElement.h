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

#include "FSUSBDevice.h"
#include "FSUSBDeviceManager.h"

#include <stack>
#include <queue>
#include <map>

namespace freestick
{
    class FSUSBJoyStickInputElement : public FSUSBDevice
    {
        /** \todo
         *typedef these private data members and other classes
         *so type of the elements can change easly if a given platform needs to
         */
        minMaxNumber _elementMin;
        minMaxNumber _elementMax;
        minMaxNumber _oldValue;
        minMaxNumber _value;
        minMaxNumber _deadZoneMin;
        minMaxNumber _deadZoneMax;
        bool _needsDeadZone;
        bool _calibrated;
        bool _intialized;
        FSUSBDeviceManager * _usbDeviceManager;
        time_t firstTime;
        std::queue<minMaxNumber> _lastValueStack;
        bool _useLastValueStack;
        u32 _parentID;
        minMaxNumber _buttonNumber;
        f32 _calibrationOffsetPrecent = 0.05f; //Offset used to calibrate deadzones

    protected:
        void calibrate(
            const physicalValueNumber currentValue
          , const minMaxNumber elementMin
          , const minMaxNumber elementMax );
        void emptyQueue(
            std::stack<FSUSBElementInfoMap>& infoMapsToReturn
          , const u32 sizeToleft);

    public:
        //FSUSBJoyStickInputElement(const & FSUSBJoyStickInputElement copy){}
        FSUSBJoyStickInputElement();
        FSUSBJoyStickInputElement(
            const u32 id
          , const u32 parentID
          , const minMaxNumber elementMin
          , const minMaxNumber elementMax
          , const vendorIDType vendorID
          , const productIDType productID
          , const FSUSBDeviceManager& _manager
          , physicalValueNumber currentValue
          , minMaxNumber buttonNumber);
        FSUSBJoyStickInputElement(
            const u32 id
          , const u32 parentID
          , const minMaxNumber elementMin
          , const minMaxNumber elementMax
          , const vendorIDType vendorID
          , const productIDType productID
          , const FSUSBDeviceManager* _manager
          , const physicalValueNumber currentValue
          , const minMaxNumber buttonNumber);
        void getMapping(
            const s32 inputValue
          , std::stack<FSUSBElementInfoMap>& infoMapsToReturn);
        minMaxNumber getValue()const{
          return _value;
        }
        void setValue(const minMaxNumber newValue);
        minMaxNumber getOldValue()const{
          return _oldValue;
        }
        bool isValueInDeadZone(const minMaxNumber value)const;
        bool isIntialized()const;
        minMaxNumber getMaxValue()const{
          return _elementMax;
        }
        minMaxNumber getMinValue()const{
          return _elementMin;
        }
        minMaxNumber getDeadZoneMin()const{
          return _deadZoneMin;
        }
        minMaxNumber getDeadZoneMax()const{
          return _deadZoneMax;
        }
        minMaxNumber getButtonNumber()const{
          return _buttonNumber;
        }
        void recalibrate(
            const physicalValueNumber currentValue
          , const minMaxNumber elementMin
          , const minMaxNumber elementMax);
        uint16_t getHIDUsage();
        uint16_t getHIDUsagePage();
        //! Used to pad out the dead zone when calibrating.
        void setCalibrationOffsetPrecent(const f32 offset);
    };
}
