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

#include "USB/platform/Windows/FSDirectInputJoystick.h"
#include "USB/common/FSUSBJoyStickInputElement.h"
#include "USB/common/FSUSBJoystickDeviceManager.h"
using namespace freestick;
FSDirectInputJoystick::FSDirectInputJoystick()
{
}


FSDirectInputJoystick::FSDirectInputJoystick(LPDIRECTINPUTDEVICE8  LPDIDJoystick,
              unsigned int joyStickID,
              unsigned int numberOfButtons,
              unsigned int numberOfAnlogSticks,
              unsigned int numberOfDigitalSticks,
              bool  forceFeedBackSupported,
              long venderID,
              long productID):FSUSBJoystick(joyStickID,numberOfButtons,numberOfAnlogSticks,numberOfDigitalSticks ,forceFeedBackSupported,venderID,productID)
{
    _LPDIDJoystick = LPDIDJoystick;

    DIPROPDWORD dipdw;
    dipdw.diph.dwSize = sizeof(DIPROPDWORD);

    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj =0;
    dipdw.diph.dwHow = DIPH_DEVICE;
   HRESULT hr = _LPDIDJoystick->GetProperty(DIPROP_VIDPID,&dipdw.diph);
    if(SUCCEEDED(hr))
    {

      WORD  vendorIDW = LOWORD(dipdw.dwData);
      WORD  productIDW = HIWORD(dipdw.dwData);
      _vendorID = vendorIDW;
      _productID = productIDW;
      _vendorIDFriendlyName = FSUSBDevice::GetFrendlyVenderNameFromID(_vendorID);
      _prodcutIDFriendlyName = FSUSBDevice::GetFrendlyProductNameFromID(_vendorID,_productID);
      _friendlyName = _vendorIDFriendlyName + " "+ _prodcutIDFriendlyName;

    }

     hr = _LPDIDJoystick->EnumObjects( FSDirectInputJoystick::EnumInputObjectsCallback,
                                               ( VOID* )this, DIDFT_ALL ) ;




}
void FSDirectInputJoystick::addButtonElement(long int usage, long int usagePage,MinMaxNumber elementId)
{
    int value = 0;
    //TODO finsh this
    //FSUSBJoyStickInputElement temp(FSUSBJoystickDeviceManager::createIdForElement(usage,usagePage),getJoystickID() ,0, 1, _vendorID,_productID,manager,value,elementId);
  //  this->addInputElement(temp);
}

BOOL CALLBACK  FSDirectInputJoystick::EnumInputObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,
                                   VOID* pContext )
{
    FSDirectInputJoystick * joystick = static_cast<FSDirectInputJoystick*>(pContext);
    static int povCount = 0;
    static int buttonCount = 0;
    if( pdidoi->guidType == GUID_POV )
    {
       povCount++;
    }
    else if(pdidoi->guidType == GUID_Button)
    {
        buttonCount++;
        joystick->addButtonElement(pdidoi->wUsage,pdidoi->wUsagePage,buttonCount);
    }
    else
    {

    }
return DIENUM_CONTINUE;
}

FSDirectInputJoystick::~FSDirectInputJoystick()
{
    if(_LPDIDJoystick)
    {
        _LPDIDJoystick->Unacquire();
    }
}
