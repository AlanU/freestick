/**************************************************************************
Created by Alan Uthoff on 10/30/2013
Copyright (C) 2015

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
#include <cstdint>
namespace freestick {

    /* TODO: rename type to lower case*/
    typedef uint32_t idNumber; //Needs to be at lest 32bits and unsigned
    typedef int32_t  minMaxNumber; //Needs to be at lest 32bits and signed
    typedef int32_t physicalValueNumber; //Needs to be at lest 32bits and signed
    typedef unsigned int elementID;
    typedef uint64_t deviceID; //Needs to be 64 bits
    typedef uint32_t vendorIDType;//Needs to be at lest 32bits
    typedef uint32_t productIDType;//Needs to be at lest 32bits
    typedef float nMinMaxNumber; //normlized max min number should be float to match system
    typedef float nPhysicalValueNumber; //normlized physical number should be float to match system
    typedef double universlalMinMaxNumber; //normlized max min number should be float to match system
    typedef double universlalPhysicalValueNumber; //normlized physical number should be float to match system

}
