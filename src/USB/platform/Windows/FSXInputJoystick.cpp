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
*/

#include "USB/platform/Windows/FSXInputJoystick.h"
#include <sstream>


using namespace freestick;
FSXInputJoystick::FSXInputJoystick(XINPUT_STATE & state,
                                   DWORD id,
                                   unsigned int joyStickID,
                                   unsigned int numberOfButtons,
                                   unsigned int numberOfAnlogSticks,
                                   unsigned int numberOfDigitalSticks,
                                   bool  forceFeedBackSupported,
                                   long vendorID,
                                   long productID,
                                   FSUSBJoystickDeviceManager & usbJoystickManager
                                   ):FSUSBJoystick( joyStickID,
                                                    numberOfButtons,
                                                    numberOfAnlogSticks,
                                                    numberOfDigitalSticks,
                                                    forceFeedBackSupported,
                                                    vendorID,
                                                    productID)
{

    std::stringstream playerNumber;
    playerNumber << id+1;

    _vendorIDFriendlyName = "XIputController";
    _productIDFriendlyName = "Player " + playerNumber.str();
    _friendlyName = _vendorIDFriendlyName + " "+ _productIDFriendlyName;
    _usbJoystickManager = &usbJoystickManager;
    _totalButtonNumber = 0;
    addXinputElements(state);

}

void FSXInputJoystick::addButtonElement(unsigned int buttonID)
{
    addElement(buttonID,0,1,0);
}

void FSXInputJoystick::addElement(unsigned int buttonID,MinMaxNumber min,MinMaxNumber max,PhysicalValueNumber currentValue)
{
    FSUSBJoyStickInputElement newElement (buttonID,getJoystickID() ,
                                   min,max, MicrosoftVendorID,MicrosoftXbox360WindowsControllerID,*_usbJoystickManager,currentValue,++_totalButtonNumber);
    this->addInputElement(newElement);
}

void FSXInputJoystick::setCalibrated()
{
    calibrated = true;
}

bool FSXInputJoystick::isCalibrated() const
{
    return calibrated;
}

void FSXInputJoystick::addXinputElements(XINPUT_STATE & state)
{

    addButtonElement(UP_DPAD_XINPUT_EID);
    addButtonElement(DOWN_DPAD_XINPUT_EID);
    addButtonElement(LEFT_DPAD_XINPUT_EID);
    addButtonElement(RIGHT_DPAD_XINPUT_EID);

    addButtonElement(A_BUTTON_XINPUT_EID);
    addButtonElement(B_BUTTON_XINPUT_EID);
    addButtonElement(X_BUTTON_XINPUT_EID);
    addButtonElement(Y_BUTTON_XINPUT_EID);

    addButtonElement(START_BUTTON_XINPUT_EID);
    addButtonElement(BACK_BUTTON_XINPUT_EID);
    addButtonElement(CENTER_BUTTON_XINPUT_EID);

    addButtonElement(LEFT_SHOULDER_BUTTON_XINPUT_EID);
    addButtonElement(RIGHT_SHOULDER_BUTTON_XINPUT_EID);


    addButtonElement(LEFT_AXIS_BUTTON_XINPUT_EID);
    addButtonElement(RIGHT_AXIS_BUTTON_XINPUT_EID);

    addElement(XAXIS_XINPUT_EID,-32768,32767,state.Gamepad.sThumbLX);
    addElement(YAXIS_XINPUT_EID,-32768,32767,state.Gamepad.sThumbLY);

    addElement(XAXIS2_XINPUT_EID,-32768,32767,state.Gamepad.sThumbRX);
    addElement(YAXIS2_XINPUT_EID,-32768,32767,state.Gamepad.sThumbRY);

    addElement(LTRIGGER_XINPUT_EID,0,255,state.Gamepad.bLeftTrigger);
    addElement(RTRIGGER_XINPUT_EID,0,255,state.Gamepad.bRightTrigger);


}
