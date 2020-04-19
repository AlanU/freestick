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

#include <string>
#include "FSUSBDevice.h"
#include "FSUSBJoyStickInputElement.h"
#include <map>

namespace freestick
{
    using JoyStickElementMap = std::map<idNumber,FSUSBJoyStickInputElement>;

    class FSUSBJoystick : public FSUSBDevice
    {
        u32 _numberOfButtons = 0;
        u32 _numberOfAnlogSticks = 0;
        u32 _numberOfDigitalSticks = 0;
        bool _forceFeedBackSupported = false;

    protected:
        JoyStickElementMap _inputElementMap{};

        FSUSBJoystick();

    public:
        virtual~FSUSBJoystick();
        FSUSBJoystick(
            const idNumber joyStickID
          , const u32 numberOfButtons
          , const u32 numberOfAnlogSticks
          , const u32 numberOfDigitalSticks
          , const bool forceFeedBackSupported
          , const vendorIDType vendorID
          , const productIDType productID );
        u32 getNumberOfButtons() const{
          return _numberOfButtons;
        }
        u32 getNumberOfAnlogSticks()const{
          return _numberOfAnlogSticks;
        }
        u32 getNumberOfDigitalSticks()const{
          return _numberOfDigitalSticks;
        }
        bool getForceFeedbackSupport()const{
          return _forceFeedBackSupported;
        }
        virtual FSDeviceType getClassType()const{
          return FSDeviceType::kUSBJoystick;
        }
        void addInputElement(FSUSBJoyStickInputElement& element);
        JoyStickElementMap getElements()const{
          return _inputElementMap;
        }
        std::vector<idNumber> getElementIds() const;
        const FSUSBJoyStickInputElement* findInputElement(idNumber id) const;
        JoyStickElementMap::const_iterator begin() const;
        JoyStickElementMap::const_iterator end() const ;
        JoyStickElementMap::iterator begin();
        JoyStickElementMap::iterator end();
    };
}
