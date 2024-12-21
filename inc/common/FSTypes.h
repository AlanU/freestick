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
    // HID Usage Pages (Human-Readable Constants)
    constexpr uint16_t HID_USAGE_PAGE_GENERIC_DESKTOP = 0x01;
    constexpr uint16_t HID_USAGE_PAGE_BUTTON = 0x09;
    constexpr uint16_t HID_USAGE_PAGE_CONSUMER = 0x0C;
    constexpr uint16_t HID_USAGE_PAGE_SIMULATION = 0x02;

    // HID Usages (Human-Readable Constants for Generic Desktop)
    constexpr uint16_t HID_USAGE_X = 0x30;
    constexpr uint16_t HID_USAGE_Y = 0x31;
    constexpr uint16_t HID_USAGE_Z = 0x32;
    constexpr uint16_t HID_USAGE_RX = 0x33;
    constexpr uint16_t HID_USAGE_RY = 0x34;
    constexpr uint16_t HID_USAGE_RZ = 0x35;
    constexpr uint16_t HID_USAGE_HAT_SWITCH = 0x39;

    // HID Usages (Human-Readable Constants for Buttons)
    constexpr uint16_t HID_USAGE_BUTTON_1 = 0x01;
    constexpr uint16_t HID_USAGE_BUTTON_2 = 0x02;
    constexpr uint16_t HID_USAGE_BUTTON_3 = 0x03;
    constexpr uint16_t HID_USAGE_BUTTON_4 = 0x04;
    constexpr uint16_t HID_USAGE_BUTTON_5 = 0x05;
    constexpr uint16_t HID_USAGE_BUTTON_6 = 0x06;
    constexpr uint16_t HID_USAGE_BUTTON_7 = 0x07;
    constexpr uint16_t HID_USAGE_BUTTON_8 = 0x08;
    constexpr uint16_t HID_USAGE_BUTTON_9 = 0x09;
    constexpr uint16_t HID_USAGE_BUTTON_10 = 0x0A;
    constexpr uint16_t HID_USAGE_BUTTON_11 = 0x0B;
    constexpr uint16_t HID_USAGE_BUTTON_12 = 0x0C;

    // Additional Buttons (A and B)
    constexpr uint16_t HID_USAGE_BUTTON_A = 0x04;  // HID Button A
    constexpr uint16_t HID_USAGE_BUTTON_B = 0x05;  // HID Button B

    // HID Usages (Human-Readable Constants for Consumer Controls)
    constexpr uint16_t HID_USAGE_VOLUME_UP = 0xE9;
    constexpr uint16_t HID_USAGE_VOLUME_DOWN = 0xEA;
    constexpr uint16_t HID_USAGE_PLAY_PAUSE = 0xCD;

    // HID Usages (Human-Readable Constants for Simulation Controls)
    constexpr uint16_t HID_USAGE_STEERING_WHEEL = 0xC0;
    constexpr uint16_t HID_USAGE_ACCELERATOR = 0xC4;
    constexpr uint16_t HID_USAGE_BRAKE = 0xC5;
}
