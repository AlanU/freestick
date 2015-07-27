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
              long productID,
              FSUSBJoystickDeviceManager & usbJoystickManager):FSUSBJoystick(joyStickID,numberOfButtons,numberOfAnlogSticks,numberOfDigitalSticks ,forceFeedBackSupported,venderID,productID)
{
    _LPDIDJoystick = LPDIDJoystick;
    _usbJoystickManager = &usbJoystickManager;
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


     // Set the cooperative level to let DInput know how this device should
     // interact with the system and with other DInput applications.
    // if( FAILED( hr = _LPDIDJoystick->SetCooperativeLevel( hDlg, DISCL_EXCLUSIVE |DISCL_FOREGROUND ) ) )

     hr = _LPDIDJoystick->EnumObjects( FSDirectInputJoystick::EnumInputObjectsCallback,
                                               ( VOID* )this, DIDFT_ALL ) ;

     // Set the data format to "simple joystick" - a predefined data format
      //
      // A data format specifies which controls on a device we are interested in,
      // and how they should be reported. This tells DInput that we will be
      // passing a DIJOYSTATE2 structure to IDirectInputDevice::GetDeviceState().
      hr = _LPDIDJoystick->SetDataFormat( &c_dfDIJoystick2 );


}
void FSDirectInputJoystick::addButtonElement(long int usage, long int usagePage,MinMaxNumber elementId)
{

 //  int value = 0;
   //TODO finsh this
   //FSUSBJoyStickInputElement temp(FSUSBJoystickDeviceManager::createIdForElement(usage,usagePage),getJoystickID() ,0, 1, _vendorID,_productID,*_usbJoystickManager,value,elementId);
    //this->addInputElement(temp);
}

void FSDirectInputJoystick::addElement(long int usage, long int usagePage,
                                       MinMaxNumber elementId,MinMaxNumber min, MinMaxNumber max,long int value)
{
    FSUSBJoyStickInputElement temp(FSUSBJoystickDeviceManager::createIdForElement(usage,usagePage),getJoystickID() ,
                                   min,max, _vendorID,_productID,*_usbJoystickManager,value,elementId);
    this->addInputElement(temp);
}


BOOL CALLBACK  FSDirectInputJoystick::EnumInputObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,
                                   VOID* pContext )
{
    DIJOYSTATE2 joystickState;
    FSDirectInputJoystick * joystick = static_cast<FSDirectInputJoystick*>(pContext);
    static int povCount = 0;
    static int buttonCount = 0;
    static int axisCount = 0;

    if( pdidoi->guidType == GUID_POV )
    {
       povCount++;
    }
    if( (pdidoi->guidType == GUID_XAxis) ||
        (pdidoi->guidType == GUID_YAxis) ||
        (pdidoi->guidType == GUID_ZAxis) ||
        (pdidoi->guidType == GUID_RxAxis)||
        (pdidoi->guidType == GUID_RyAxis)||
        (pdidoi->guidType == GUID_RzAxis))
    {



        DIPROPRANGE range;
        range.diph.dwSize = sizeof(DIPROPRANGE);
        range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        range.diph.dwHow = DIPH_BYID;
        range.diph.dwObj = pdidoi->dwType;
        MinMaxNumber min = 0;
        MinMaxNumber max = 0;

        if ( joystick->getDirectInputPtr()->GetProperty(DIPROP_LOGICALRANGE, &range.diph) == DI_OK)
        {
           min  = range.lMin;
           max  = range.lMax;
           long int value = max/2;
           DIPROPRANGE diprg;
           diprg.diph.dwSize=sizeof( DIPROPRANGE );
           diprg.diph.dwHeaderSize=sizeof( DIPROPHEADER );
           diprg.diph.dwHow=DIPH_BYID;
           diprg.diph.dwObj= pdidoi->dwType;
           diprg.lMin=min;
           diprg.lMax=max;
           if(  joystick->getDirectInputPtr()->SetProperty( DIPROP_RANGE, &diprg.diph )== DI_OK)
           {
             joystick->addElement(pdidoi->wUsage,pdidoi->wUsagePage,buttonCount,min,max,value);
           }
        }


       axisCount++;
    }
    else if(pdidoi->guidType == GUID_Button)
    {
        buttonCount++;
        joystick->addElement(pdidoi->wUsage,pdidoi->wUsagePage,buttonCount,0,1,0);
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
