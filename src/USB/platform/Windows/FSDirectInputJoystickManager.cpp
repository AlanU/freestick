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

#include "USB/platform/Windows/FSDirectInputJoystickManager.h"
#include "USB/platform/Windows/FSDirectInputJoystick.h"
#include <hidusage.h>
#include <chrono>
#include <string.h>
//This is a work around for VS 2013 not supporting constexpr correctly
//This should be change to constexpr once 2013 support is dropped
const std::chrono::milliseconds connectionCheckSleep(1500);
using namespace freestick;


FSDirectInputJoystickManager::FSDirectInputJoystickManager()
{
    //sets the atomic_flag to false before use
    //This is a work around for VS 2013 not supporting
    //std::atomic_flag locked = ATOMIC_FLAG_INIT
    //Once VS 2013 is droped this code should be changed back
    lookingForJoysticks.clear();
    _directInput8 = NULL;
}

void FSDirectInputJoystickManager::init( )
{
    HRESULT hr;

    if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_directInput8, NULL)))
        return;


    PreferredJoyCfg;
    enumContext.joystickConfig = &PreferredJoyCfg;
    enumContext.isVaild = false;
    enumContext.manager = this;

    IDirectInputJoyConfig * joyConfig;
    if (FAILED(hr = _directInput8->QueryInterface(IID_IDirectInputJoyConfig8, (void**)&joyConfig) ))
        enumContext.isVaild = true;
    if(joyConfig)
    {
        joyConfig->Release();
        joyConfig = nullptr;
    }
    lookingForJoysticks.test_and_set(std::memory_order_relaxed);
    std::unique_ptr<std::thread>  connectThread (
                new std::thread(&freestick::FSDirectInputJoystickManager::updateConnectJoysticks,this));
    connectedJoystickThread = std::move(connectThread);
    update();


}

void FSDirectInputJoystickManager::updateConnectJoysticks()
{
    while(lookingForJoysticks.test_and_set(std::memory_order_acquire))
    {
        HRESULT hr;
        std::vector<GUID> newThisUpdate;
        std::vector<GUID> foundThisUpdate;

        if (SUCCEEDED( hr = _directInput8->EnumDevices(DI8DEVCLASS_GAMECTRL,
                                   FSDirectInputJoystickManager::EnumJoysticksCallback,
                                   &enumContext,
                                   DIEDFL_ATTACHEDONLY))) {
            for ( std::vector<GUID>::iterator itr =  enumContext.joysticksConnectedThisUpdate.begin(); itr != enumContext.joysticksConnectedThisUpdate.end(); ++itr) {
                GUID foundJoystick = *itr;
                std::vector<GUID>::iterator itr2 = std::find(enumContext.connectedLastUpdateJoysticks.begin(),
                                        enumContext.connectedLastUpdateJoysticks.end(),
                                        foundJoystick);
                if (itr2 != enumContext.connectedLastUpdateJoysticks.end()) {
                    enumContext.connectedLastUpdateJoysticks.erase(itr2);

                }else  {
                    newThisUpdate.push_back(foundJoystick);
                }
                foundThisUpdate.push_back(foundJoystick);

            }
            for (int index =(int) enumContext.connectedLastUpdateJoysticks.size() - 1; index >= 0; index--) {
                GUID deviceToDelete = enumContext.connectedLastUpdateJoysticks[index];
                this->removeDevice(deviceToDelete );
            }
            std::vector<GUID>::iterator itrAdd;
            for (itrAdd = newThisUpdate.begin(); itrAdd != newThisUpdate.end(); ++itrAdd ) {
                this->addDevice(*itrAdd);

            }

            enumContext.connectedLastUpdateJoysticks = foundThisUpdate;
            enumContext.joysticksConnectedThisUpdate.clear();

          std::this_thread::sleep_for(connectionCheckSleep);
        }
   }
}

void FSDirectInputJoystickManager::update()
{
    connectedJoystickLock.lock();
    for( FSDirectInputJoystick * &joystickToAdd : joysticksToAddThisUpdate )
    {
        addDevice(joystickToAdd);

    }
    joysticksToAddThisUpdate.clear();
    for( const FSBaseDevice *  &joystickToRemove : joysticksToRemoveThisUpdate )
    {
        removeDevice((FSBaseDevice*)joystickToRemove);

    }
    joysticksToRemoveThisUpdate.clear();
    connectedJoystickLock.unlock();
    updateJoysticks();
}

void FSDirectInputJoystickManager::updateJoysticksPOV(FSDirectInputJoystick & device, LONG axisValue, long int idForXAxis)
{
    FSDeviceInput povInput = LastInput;
    if (axisValue == -1) {
        povInput = LastValueUp;

    }else if (axisValue == 102 ) {
        povInput = DPadRight;

    }else if (axisValue == 308 ) {
        povInput = DPadLeft;

    }else if ((axisValue >= 0 && axisValue < 102) || axisValue > 308) {
        povInput = DPadUp;
    }else  {
        povInput = DPadDown;

    }

   if(lastPOVValue[device.getJoystickID()] != axisValue)
    {
        FSUSBElementInfoMap temp = this->infoMapForInputType(device.getVendorID(), device.getProductID(), povInput);
        if (temp.getDeviceInput() != LastInput && temp.getEventMapping() != FSLastEventAction ) {
            FSUSBJoyStickInputElement * element = (FSUSBJoyStickInputElement*)device.findInputElement(idForXAxis);
            if (element!= NULL) {

                if (!element->isIntialized())
                {
                    std::stack<FSUSBElementInfoMap> inputTypes;
                    element->getMapping(temp.getMin(), inputTypes);
                }
                FSUSBJoystickDeviceManager::updateEvents(device.getJoystickID(), element, temp.getMin());
               // updateEvents(device.getJoystickID(), element,  temp.getMin());
            }
        }
    }
   lastPOVValue[device.getJoystickID()] = axisValue;

}
void FSDirectInputJoystickManager::updateJoysticksAxis(FSDirectInputJoystick & device, LONG axisValue, long int idForXAxis)
{
    FSUSBJoyStickInputElement * element = const_cast<FSUSBJoyStickInputElement*>(device.findInputElement(idForXAxis));

    if (element) {
        if (device.isCalibrated()) {
            element->recalibrate(axisValue, element->getMinValue(), element->getMaxValue());
            return;
        }
        if (element->getValue() != axisValue) {
            updateEvents(device.getJoystickID(), element, axisValue);
        }
    }

}

void FSDirectInputJoystickManager::updateJoysticks()
{
    // DInput joystick state
    if (!deviceMap.empty()) {
        std::unordered_map<unsigned int, FSBaseDevice * >::iterator itr;
        for (itr = deviceMap.begin(); itr != deviceMap.end(); ++itr) {
            FSDirectInputJoystick * device = static_cast<FSDirectInputJoystick *>(itr->second);

            if(device == nullptr)
            {
                continue;
            }

            LPDIRECTINPUTDEVICE8 directInputJoystick = device->getDirectInputPtr();
            HRESULT hr;
            DIJOYSTATE2 js;
            // Poll the device to read the current state
            hr = directInputJoystick->Poll();
            if ( FAILED( hr ) ) {
                // DInput is telling us that the input stream has been
                // interrupted. We aren't tracking any state between polls, so
                // we don't have any special reset that needs to be done. We
                // just re-acquire and try again.
                hr = directInputJoystick->Acquire();

                while ( hr == DIERR_INPUTLOST )
                    hr = directInputJoystick->Acquire();

                if (hr == DI_OK || hr == S_FALSE  ) {
                    hr = directInputJoystick->Poll();
                    if ( FAILED( hr ) ) {
                        continue;
                    }
                }else  {
                    // hr may be DIERR_OTHERAPPHASPRIO or other errors.  This
                    // may occur when the app is minimized or in the process of
                    // switching, so just try again later
                    continue;
                }

            }

            // Get the input's device state
            if ( FAILED( hr = directInputJoystick->GetDeviceState( sizeof( DIJOYSTATE2 ), &js ) ) )
                continue; // The device should have been acquired during the Poll()


            //TODO put this in a std::array<ipair<hex,hex>> to
            //X-axis
            long int idForAxis =  FSUSBJoystickDeviceManager::createIdForElement(HID_USAGE_GENERIC_X, HID_USAGE_PAGE_GENERIC);

            updateJoysticksAxis(*device, js.lX, idForAxis);
            //Yaxis
            idForAxis =  FSUSBJoystickDeviceManager::createIdForElement(HID_USAGE_GENERIC_Y, HID_USAGE_PAGE_GENERIC);
            updateJoysticksAxis(*device, js.lY, idForAxis);

            //zaxis
            idForAxis =  FSUSBJoystickDeviceManager::createIdForElement(HID_USAGE_GENERIC_Z, HID_USAGE_PAGE_GENERIC);
            updateJoysticksAxis(*device, js.lZ, idForAxis);

            //rxaxis
            idForAxis =  FSUSBJoystickDeviceManager::createIdForElement(HID_USAGE_GENERIC_RX, HID_USAGE_PAGE_GENERIC);
            updateJoysticksAxis(*device, js.lRx, idForAxis);

            //ryaxis
            idForAxis =  FSUSBJoystickDeviceManager::createIdForElement(HID_USAGE_GENERIC_RY, HID_USAGE_PAGE_GENERIC);
            updateJoysticksAxis(*device, js.lRy, idForAxis);

            //rzaxis
            idForAxis =  FSUSBJoystickDeviceManager::createIdForElement(HID_USAGE_GENERIC_RZ, HID_USAGE_PAGE_GENERIC);
            updateJoysticksAxis(*device, js.lRz, idForAxis);

            //slider
            idForAxis =  FSUSBJoystickDeviceManager::createIdForElement(HID_USAGE_GENERIC_RZ, HID_USAGE_PAGE_GENERIC);
            updateJoysticksAxis(*device, js.lRz, idForAxis);


            //TODO map POV to DPadUp DPadDown DPadLeft DPadRight
            idForAxis = FSUSBJoystickDeviceManager::createIdForElement(HID_USAGE_GENERIC_HATSWITCH, HID_USAGE_PAGE_GENERIC);
            long angleValue = -1;
            //convert to an angle 0 - 360 to fit into a long
            if (js.rgdwPOV[0] != -1) {
                double leftSpan = 31500;
                double rightSpan = 360;

                double valueScaled = ((double )js.rgdwPOV[0]) / double(leftSpan);
                angleValue = (long)(valueScaled * rightSpan);
            }
            updateJoysticksPOV(*device, angleValue, idForAxis);

			int buttonNumber = 0;

			for  (auto & item : *device)
			{
				FSUSBJoyStickInputElement & element = item.second;
				if (element.getMinValue() == 0 && element.getMaxValue() == 1) {
                    minMaxNumber value = (js.rgbButtons[buttonNumber] & 0x80) ? 1 : 0;

                    if (element.getValue() != value) {
						updateEvents(device->getJoystickID(),&element, value);
					}
					buttonNumber++;
				}
			}
        }

    }
}

FSDirectInputJoystickManager::~FSDirectInputJoystickManager()
{
    lookingForJoysticks.clear(std::memory_order_release);
    connectedJoystickThread.get()->join();

}


BOOL CALLBACK FSDirectInputJoystickManager::EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, void* pContext )
{
    DirectInput_Enum_Contex * enumContext = reinterpret_cast<DirectInput_Enum_Contex *>(pContext);

    if (IsXInputDeviceRaw(&pdidInstance->guidProduct))
        return DIENUM_CONTINUE;

    // Skip anything other than the perferred joystick device as defined by the control panel.
    // Instead you could store all the enumerated joysticks and let the user pick.
    if ( enumContext->isVaild && !IsEqualGUID( pdidInstance->guidInstance, enumContext->joystickConfig->guidInstance ) )
        return DIENUM_CONTINUE;

    enumContext->joysticksConnectedThisUpdate.push_back(pdidInstance->guidInstance);


    return DIENUM_CONTINUE;
}

void FSDirectInputJoystickManager::addDevice(FSBaseDevice * device)
{
    FSUSBJoystickDeviceManager::addDevice(device);
    lastPOVValue[device->getJoystickID()] = -1;
}

void FSDirectInputJoystickManager::removeDevice(FSBaseDevice * device)
{
    lastPOVValue.erase(device->getJoystickID());
    FSUSBJoystickDeviceManager::removeDevice(device);

}

void FSDirectInputJoystickManager::addDevice(GUID guidDeviceInstance)
{
    std::lock_guard<ConnctionLockType> lock(connectedJoystickLock);
    if (_directInputToDeviceIDMap.find(guidDeviceInstance) == _directInputToDeviceIDMap.end()) {
        LPDIRECTINPUTDEVICE8 _Joystick = NULL;
        HRESULT result;
        result = _directInput8->CreateDevice(guidDeviceInstance, &_Joystick, NULL);
        if (SUCCEEDED(result)) {
            //TODO set up event with SetEventNotification , CreateEvent , and WaitForSingleObject
            elementID newID = this->getNextID();
            FSDirectInputJoystick * newJoystick = new FSDirectInputJoystick(_Joystick, newID, 0, 0, 0, false, -1, -1, *this);
            joysticksToAddThisUpdate.push_back(newJoystick);
            //  this->addDevice(newJoystick);
            _directInputToDeviceIDMap[guidDeviceInstance] = newID;
        }
    }
}

void FSDirectInputJoystickManager::removeDevice(GUID guidDeviceInstance)
{
    std::lock_guard<ConnctionLockType> lock (connectedJoystickLock);
    if (_directInputToDeviceIDMap.find(guidDeviceInstance) != _directInputToDeviceIDMap.end()) {
       elementID id = _directInputToDeviceIDMap[guidDeviceInstance];
        const FSBaseDevice * joystickToDelete = this->getDevice(id);
        joysticksToRemoveThisUpdate.push_back(joystickToDelete);
        //this->removeDevice((FSBaseDevice*)joystickToDelete);
        _directInputToDeviceIDMap.erase(guidDeviceInstance);
    }
}


//Check each device using RAW HID to see if the device contains "IG_" if so it is a Xinput device.
bool FSDirectInputJoystickManager::IsXInputDeviceRaw( const GUID* pGuidProductFromDirectInput )
{
    bool isXInputDevice = false;
    UINT nDevices, nDeviceCount;
    PRAWINPUTDEVICELIST pRawInputDeviceList;
    if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0)
    {
        return false;
    }

    //TODO remove malloc and free and use std::Array
    pRawInputDeviceList = static_cast<RAWINPUTDEVICELIST *>(malloc(sizeof(RAWINPUTDEVICELIST) * nDevices));
    if (pRawInputDeviceList == NULL)
    {
        return false;
    }

    nDeviceCount = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST));
    if (nDeviceCount == (UINT)-1)
    {
       free(pRawInputDeviceList);
       return false;
    }

    for(UINT index = 0 ; index < nDeviceCount; ++index)
    {
        if(pRawInputDeviceList[index].dwType == RIM_TYPEHID)
        {
            RID_DEVICE_INFO ridDeviceInfo;
            UINT cbSizeTemp = ridDeviceInfo.cbSize = sizeof(ridDeviceInfo);

            if((INT)GetRawInputDeviceInfoA(pRawInputDeviceList[index].hDevice,RIDI_DEVICEINFO,&ridDeviceInfo,&cbSizeTemp)>0)
            {
                if(MAKELONG(ridDeviceInfo.hid.dwVendorId, ridDeviceInfo.hid.dwProductId) == (LONG)pGuidProductFromDirectInput->Data1 )
                {
                    char deviceName[256] = {'\0'};
                    UINT deviceNameLength = std::extent< decltype( deviceName ) >::value;
                    UINT resultLength =  GetRawInputDeviceInfoA(pRawInputDeviceList[index].hDevice,RIDI_DEVICENAME,deviceName,&deviceNameLength);
                   if(resultLength != (UINT)-1)
                   {

                       isXInputDevice = (strstr(deviceName,"IG_") != nullptr);
                       break;
                   }
                }
            }
        }
    }
    free(pRawInputDeviceList);
    return isXInputDevice;
}
