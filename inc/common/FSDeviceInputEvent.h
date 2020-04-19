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

#include "../baseClasses/FSBaseEvent.h"
#include "../Interfaces/IFSDevice.h"
#include "./common/FSTypes.h"

#if MSVC_2013_AND_EARLIER
  static const freestick::f32 MAX_EVENT_VALUE =  1.f;
  static const freestick::f32 MIN_EVENT_VALUE = -1.f;
#else
  constexpr f32 MAX_EVENT_VALUE =  1.f;
  constexpr f32 MIN_EVENT_VALUE = -1.f;
#endif

namespace freestick
{
    class FSDeviceInputEvent : public FSBaseEvent
    {
        f32 _oldValue;
        f32 _newValue;
        u32 _controlID;
        FSDeviceInput _inputType;

    public:
        FSDeviceInputEvent() = delete;
        FSDeviceInputEvent(
              const FreeStickEventType eventType
            , const FSEventAction eventAction
            , const u32 timeStamp
            , const idNumber deviceID
            , const u32 controlID
            , const f32 oldValue
            , const f32 newValue
            , const FSDeviceInput inputType);
        f32 getOldInputValue()const{
          return _oldValue;
        }
        f32 getNewInputValue()const{
          return _newValue;
        }
        int getControlID()const{
          return _controlID;
        }
        FSDeviceInput getInputType()const{
          return _inputType;
        }
    };
}
