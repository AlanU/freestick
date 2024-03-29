/**************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2015.

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
#include "USB/common/FSUpdatableJoystickDeviceManager.h"
#include "USB/platform/Windows/FSDirectInputJoystick.h"
#include "common/FSSpinlock.h"
#define DIRECTINPUT_VERSION 0x0800
#define WIN32_LEAN_AND_MEAN
#include <dinput.h>
#include <dinputd.h>
#include <mutex>
#include <memory>
#include <thread>
#include <atomic>

inline bool operator<( const GUID & lhs, const GUID & rhs )
{
        return  memcmp(&lhs, &rhs, sizeof(GUID) )< 0;
}

namespace freestick {
    class FSDirectInputJoystickManager;
    struct DirectInput_Enum_Contex
    {
        DIJOYCONFIG * joystickConfig;
        bool isVaild;
        freestick::FSDirectInputJoystickManager * manager;
        std::vector<GUID> connectedLastUpdateJoysticks;
        std::vector<GUID> joysticksConnectedThisUpdate;
    };

    class FSDirectInputJoystickManager : public FSUpdatableJoystickDeviceManager
    {
    public:
        FSDirectInputJoystickManager();
        virtual void init( );
        virtual void update();
        virtual ~FSDirectInputJoystickManager();
        static bool IsXInputDeviceRaw( const GUID* pGuidProductFromDirectInput );
        //Windows BOOL is type def for int
        static BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance,void* pContext );
        static BOOL CALLBACK EnumInputObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,VOID* pContext );

    private:

        LPDIRECTINPUT8          _directInput8;

        std::map<GUID,unsigned int> _directInputToDeviceIDMap;
        DIJOYCONFIG PreferredJoyCfg;
        DirectInput_Enum_Contex enumContext;
    protected:
        virtual void addDevice(FSBaseDevice * device);
        virtual void removeDevice(FSBaseDevice * device);
        virtual void addDevice(GUID guidDeviceInstance);
        virtual void removeDevice(GUID guidDeviceInstance);
        void updateJoysticksAxis(FSDirectInputJoystick & device,LONG axisValue, long int idForXAxis);
        void updateJoysticksPOV(FSDirectInputJoystick & device,LONG axisValue, long int idForXAxis);

        void updateJoysticks();
    private:
        std::unordered_map<idNumber,LONG> lastPOVValue;
        typedef FSSpinLock ConnctionLockType ;
        ConnctionLockType connectedJoystickLock;
        std::vector<FSDirectInputJoystick * > joysticksToAddThisUpdate;
        std::vector<const FSBaseDevice * > joysticksToRemoveThisUpdate;
        std::unique_ptr<std::thread> connectedJoystickThread;
        void updateConnectJoysticks();
        FSSpinLock spinLock;
        std::atomic_flag lookingForJoysticks;
    };


}
