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

#pragma once
#include "IFSEvent.h"
#include "../baseClasses/FSBaseEvent.h"
#include "../common/FSDeviceInputEvent.h"
namespace freestick
{
    class IFSJoystickListener
    {
    public:
        virtual void onButtonDown(FSDeviceInputEvent event) = 0;
        virtual void onButtonUp(FSDeviceInputEvent event) = 0;
        virtual void onStickMove(FSDeviceInputEvent event) = 0;
        virtual void onDisconnect(FSBaseEvent event) = 0;
        virtual void onConnect(FSBaseEvent event) = 0;
        virtual void onUnknownChanged(FSDeviceInputEvent event) {}
    };
}
