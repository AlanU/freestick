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

#include <cstdint>

/** \brief The Freestick namespace.
  *
  * This namespace contains all types, classes, structs and unions pertinent to
  * the freestick library functionality.
  */

namespace freestick
{
    /* Duplicate Linux driver/game types */

    using u64 = uint64_t; //!< 64-bit unsigned integer.
    using s64 =  int64_t; //!< 64-bit signed integer.
    using u32 = uint32_t; //!< 32-bit unsigned integer.
    using s32 =  int32_t; //!< 32-bit signed integer.
    using u16 = uint16_t; //!< 16-bit unsigned integer.
    using s16 =  int16_t; //!< 16-bit signed integer.
    using u8  =  uint8_t; //!< 8-bit unsigned integer.
    using s8  =   int8_t; //!< 8-bit signed integer.

    /* Define floating point types */

    using f64 = double;
    using f32 = float;

    /* Define freestick types */

    using idNumber                     = u32;//!< Needs to be at least 32bits and unsigned
    using minMaxNumber                 = s32;//!< Needs to be at least 32bits and signed
    using physicalValueNumber          = s32;//!< Needs to be at least 32bits and signed
    using elementID                    = u32;
    using deviceID                     = u64;//!< Needs to be 64 bits
    using vendorIDType                 = u32;//!< Needs to be at least 32bits
    using productIDType                = u32;//!< Needs to be at least 32bits
    using nMinMaxNumber                = f32;//!< Normalized max min number should be float to match system
    using nPhysicalValueNumber         = f32;//!< Normalized physical number should be float to match system
    using universalMinMaxNumber        = f64;//!< Normalized max min number should be float to match system
    using universalPhysicalValueNumber = f64;//!< Normalized physical number should be float to match system
}

/* Microsoft defines
 *
 * MSVC++ 14.24 _MSC_VER == 1924 (Visual Studio 2019 version 16.4.5)
 * MSVC++ 14.23 _MSC_VER == 1923 (Visual Studio 2019 version 16.3)
 * MSVC++ 14.22 _MSC_VER == 1922 (Visual Studio 2019 version 16.2)
 * MSVC++ 14.21 _MSC_VER == 1921 (Visual Studio 2019 version 16.1)
 * MSVC++ 14.2  _MSC_VER == 1920 (Visual Studio 2019 version 16.0)
 * MSVC++ 14.16 _MSC_VER == 1916 (Visual Studio 2017 version 15.9)
 * MSVC++ 14.15 _MSC_VER == 1915 (Visual Studio 2017 version 15.8)
 * MSVC++ 14.14 _MSC_VER == 1914 (Visual Studio 2017 version 15.7)
 * MSVC++ 14.13 _MSC_VER == 1913 (Visual Studio 2017 version 15.6)
 * MSVC++ 14.12 _MSC_VER == 1912 (Visual Studio 2017 version 15.5)
 * MSVC++ 14.11 _MSC_VER == 1911 (Visual Studio 2017 version 15.3)
 * MSVC++ 14.1  _MSC_VER == 1910 (Visual Studio 2017 version 15.0)
 * MSVC++ 14.0  _MSC_VER == 1900 (Visual Studio 2015 version 14.0)
 * MSVC++ 12.0  _MSC_VER == 1800 (Visual Studio 2013 version 12.0)
 * MSVC++ 11.0  _MSC_VER == 1700 (Visual Studio 2012 version 11.0)
 * MSVC++ 10.0  _MSC_VER == 1600 (Visual Studio 2010 version 10.0)
 * MSVC++ 9.0   _MSC_FULL_VER == 150030729 (Visual Studio 2008, SP1)
 * MSVC++ 9.0   _MSC_VER == 1500 (Visual Studio 2008 version 9.0)
 * MSVC++ 8.0   _MSC_VER == 1400 (Visual Studio 2005 version 8.0)
 * MSVC++ 7.1   _MSC_VER == 1310 (Visual Studio .NET 2003 version 7.1)
 * MSVC++ 7.0   _MSC_VER == 1300 (Visual Studio .NET 2002 version 7.0)
 * MSVC++ 6.0   _MSC_VER == 1200 (Visual Studio 6.0 version 6.0)
 * MSVC++ 5.0   _MSC_VER == 1100 (Visual Studio 97 version 5.0)
 */

#if _MSC_VER <= 1800
  #define MSVC_2013_AND_EARLIER 1
#endif
