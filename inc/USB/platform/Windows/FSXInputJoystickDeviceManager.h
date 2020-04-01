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

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define NOMINMAX
#include <Windows.h>
#include <Xinput.h>

#include "USB/common/FSUpdatableJoystickDeviceManager.h"
#include "USB/platform/Windows/FSXInputJoystick.h"

namespace freestick
{
    class FSXInputJoystickDeviceManager : public FSUpdatableJoystickDeviceManager
    {
        std::map<DWORD,u32> _wordToIDControllerMap;
        std::vector<DWORD> _connectedLastUpdateJoysticks;

        void removeXInputDevice(const DWORD device);
        void addXInputDevice(
            const DWORD device
          , XINPUT_STATE& xState);
        void updateButton(
            const WORD buttons
          , const WORD xButtonToLookFor
          , const u32 buttonToLookFor
          , const FSXInputJoystick* xinputJoystick
          , const u32 controllerID);
        void updateAnalog(
            const u32 axisToLookFor
          , const FSXInputJoystick* xinputJoystick
          , const u32 controllerID
          , const physicalValueNumber value );
        void updateConnectJoysticks();
        void updateJoysticks();

    public:
        FSXInputJoystickDeviceManager();
        virtual void update();
    };
}
