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
FSXInputJoystick::FSXInputJoystick(DWORD id,
                                   unsigned int joyStickID,
                                   unsigned int numberOfButtons,
                                   unsigned int numberOfAnlogSticks,
                                   unsigned int numberOfDigitalSticks,
                                   bool  forceFeedBackSupported,
                                   long venderID,
                                   long productID,
                                   FSUSBJoystickDeviceManager & usbJoystickManager
                                   ):FSUSBJoystick( joyStickID,
                                                    numberOfButtons,
                                                    numberOfAnlogSticks,
                                                    numberOfDigitalSticks,
                                                    forceFeedBackSupported,
                                                    venderID,
                                                    productID)
{

    std::stringstream playerNumber;
    playerNumber << id+1;

    _vendorIDFriendlyName = "XIputController";
    _prodcutIDFriendlyName = "Player " + playerNumber.str();
    _friendlyName = _vendorIDFriendlyName + " "+ _prodcutIDFriendlyName;
    _usbJoystickManager = &usbJoystickManager;
    _totalButtonNumber = 0;
    addXinputElements();

}

void FSXInputJoystick::addButtonElement(unsigned int buttonID)
{
    FSUSBJoyStickInputElement upDpad(buttonID,getJoystickID() ,
                                   0,1, MicrosoftVendorID,MicrosoftXbox360WindowsControllerID,*_usbJoystickManager,0,++_totalButtonNumber);
    this->addInputElement(upDpad);
}

void FSXInputJoystick::addXinputElements()
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


}
