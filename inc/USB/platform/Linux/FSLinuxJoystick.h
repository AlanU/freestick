/**************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2024.

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

#include "USB/common/FSUSBJoystick.h"
#include "USB/common/FSUSBJoystickDeviceManager.h"
#include "common/FSTypes.h"
#include <libevdev/libevdev.h>
#include <unordered_map>
namespace freestick
{
    class FSLinuxJoystick : public FSUSBJoystick
    {
    public:
        // Helper function to combine event_type and event_code into a single uint32_t key
        static constexpr uint32_t makeKey(uint16_t event_type, uint16_t event_code) {
            return (static_cast<uint32_t>(event_type) << 16) | event_code;
        }

        // Structure to store HID Usage and Usage Page
        struct HIDMapping {
            uint16_t usage_page = 0;
            uint16_t usage = 0;
        };
        static std::unordered_map<uint32_t, HIDMapping> createEventToHIDMapping() {
            static std::unordered_map<uint32_t, HIDMapping> hidMap {
                    // Generic Desktop Page
                    {makeKey(EV_ABS, ABS_X),      {HID_USAGE_PAGE_GENERIC_DESKTOP, HID_USAGE_X}},
                    {makeKey(EV_ABS, ABS_Y),      {HID_USAGE_PAGE_GENERIC_DESKTOP, HID_USAGE_Y}},
                    {makeKey(EV_ABS, ABS_Z),      {HID_USAGE_PAGE_GENERIC_DESKTOP, HID_USAGE_Z}},
                    {makeKey(EV_ABS, ABS_RX),     {HID_USAGE_PAGE_GENERIC_DESKTOP, HID_USAGE_RX}},
                    {makeKey(EV_ABS, ABS_RY),     {HID_USAGE_PAGE_GENERIC_DESKTOP, HID_USAGE_RY}},
                    {makeKey(EV_ABS, ABS_RZ),     {HID_USAGE_PAGE_GENERIC_DESKTOP, HID_USAGE_RZ}},
                    {makeKey(EV_ABS, ABS_HAT0X),  {HID_USAGE_PAGE_GENERIC_DESKTOP, HID_USAGE_HAT_SWITCH}},
                    {makeKey(EV_ABS, ABS_HAT0Y),  {HID_USAGE_PAGE_GENERIC_DESKTOP, HID_USAGE_HAT_SWITCH}},

                    // Buttons Page
                    {makeKey(EV_KEY, BTN_0),      {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_1}},
                    {makeKey(EV_KEY, BTN_1),      {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_2}},
                    {makeKey(EV_KEY, BTN_2),      {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_3}},
                    {makeKey(EV_KEY, BTN_3),      {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_4}},
                    {makeKey(EV_KEY, BTN_A),      {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_A}},
                    {makeKey(EV_KEY, BTN_B),      {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_B}},

                    // Buttons Page
                    {makeKey(EV_KEY, BTN_TRIGGER), {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_1}},
                    {makeKey(EV_KEY, BTN_THUMB),   {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_2}},
                    {makeKey(EV_KEY, BTN_THUMB2),  {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_3}},
                    {makeKey(EV_KEY, BTN_TOP),     {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_4}},
                    {makeKey(EV_KEY, BTN_TOP2),    {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_5}},
                    //{makeKey(EV_KEY, BTN_PINKIE),  {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_6}},
                {makeKey(EV_KEY, BTN_BASE6),    {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_6}},
                    {makeKey(EV_KEY, BTN_BASE),   {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_7}},
                    {makeKey(EV_KEY, BTN_BASE2),   {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_8}},
                    {makeKey(EV_KEY, BTN_BASE3),   {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_9}},
                    {makeKey(EV_KEY, BTN_BASE4),   {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_10}},
                    {makeKey(EV_KEY, BTN_BASE5),   {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_11}},

                    // Button A and B
                    {makeKey(EV_KEY, BTN_A),       {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_A}},
                    {makeKey(EV_KEY, BTN_B),       {HID_USAGE_PAGE_BUTTON, HID_USAGE_BUTTON_B}},

                    // Consumer Page
                    {makeKey(EV_KEY, KEY_VOLUMEUP),   {HID_USAGE_PAGE_CONSUMER, HID_USAGE_VOLUME_UP}},
                    {makeKey(EV_KEY, KEY_VOLUMEDOWN), {HID_USAGE_PAGE_CONSUMER, HID_USAGE_VOLUME_DOWN}},
                    {makeKey(EV_KEY, KEY_PLAYPAUSE),  {HID_USAGE_PAGE_CONSUMER, HID_USAGE_PLAY_PAUSE}},

                    // Simulation Controls Page
                    {makeKey(EV_ABS, ABS_WHEEL),  {HID_USAGE_PAGE_SIMULATION, HID_USAGE_STEERING_WHEEL}},
                    {makeKey(EV_ABS, ABS_GAS),    {HID_USAGE_PAGE_SIMULATION, HID_USAGE_ACCELERATOR}},
                    {makeKey(EV_ABS, ABS_BRAKE),  {HID_USAGE_PAGE_SIMULATION, HID_USAGE_BRAKE}},
                    };
            return hidMap;
        }
        static HIDMapping getHIDUsageAndPage(uint16_t event_type, uint16_t event_code);
        FSLinuxJoystick(idNumber joyStickID,
                        const std::string & devicePath,
                        vendorIDType vendorID,
                        productIDType productID,
                        FSUSBJoystickDeviceManager & usbJoystickManager);
        ~FSLinuxJoystick() override;
        libevdev * getHandel();
        int32_t getDpadDeviceInput(uint16_t type, uint16_t code, int32_t value);

    private:
        std::string m_devicePath;
        libevdev * m_evdevHandel = nullptr;
        int m_openFileHandler = -1;
        bool m_isHatSwitchDpad = false;
        bool m_isMapped = false;
        FSUSBJoystickDeviceManager * m_usbJoystickManager = nullptr;
    };
}
