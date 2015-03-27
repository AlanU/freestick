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

using namespace freestick;



FSDirectInputJoystickManager::FSDirectInputJoystickManager()
{
    _directInput8 = NULL;
}


void FSDirectInputJoystickManager::init( )
{
    HRESULT hr ;

    if(FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,IID_IDirectInput8,(void **)&_directInput8,NULL)))
        return;


    //TODO filter out xinput devices

    PreferredJoyCfg ;
   // DirectInput_Enum_Contex enumContext;
    enumContext.joystickConfig = &PreferredJoyCfg;
    enumContext.isVaild = false;
    enumContext.manager = this;

    IDirectInputJoyConfig * joyConfig;
    if(FAILED(hr = _directInput8->QueryInterface(IID_IDirectInputJoyConfig8,(void**)&joyConfig) ))
        enumContext.isVaild = true;
    SAFE_RELEASE(joyConfig);

    if(FAILED( hr = _directInput8->EnumDevices(DI8DEVCLASS_GAMECTRL,
                                               FSDirectInputJoystickManager::EnumJoysticksCallback,
                                               &enumContext,
                                               DIEDFL_ATTACHEDONLY)))
        return;

}

void FSDirectInputJoystickManager::update()
{
    //TODO loop through connected joysticks and update there data
    HRESULT hr ;

    if(FAILED( hr = _directInput8->EnumDevices(DI8DEVCLASS_GAMECTRL,
                                               FSDirectInputJoystickManager::EnumJoysticksCallback,
                                               &enumContext,
                                               DIEDFL_ATTACHEDONLY)))
        return;
}

FSDirectInputJoystickManager::~FSDirectInputJoystickManager()
{

}

 BOOL CALLBACK FSDirectInputJoystickManager::EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance,void* pContext )
{
     DirectInput_Enum_Contex * enumContext = reinterpret_cast<DirectInput_Enum_Contex *>(pContext);
    // HRESULT hr;

     if(IsXInputDevice(&pdidInstance->guidProduct))
         return DIENUM_CONTINUE;

     // Skip anything other than the perferred joystick device as defined by the control panel.
     // Instead you could store all the enumerated joysticks and let the user pick.
     if( enumContext->isVaild && !IsEqualGUID( pdidInstance->guidInstance, enumContext->joystickConfig->guidInstance ) )
         return DIENUM_CONTINUE;

     enumContext->manager->addDevice(pdidInstance->guidInstance);


return DIENUM_CONTINUE;
}

void  FSDirectInputJoystickManager::addDevice(FSBaseDevice * device)
{
    FSUSBJoystickDeviceManager::addDevice(device);
}

void  FSDirectInputJoystickManager::removeDevice(FSBaseDevice * device)
{
    FSUSBJoystickDeviceManager::removeDevice(device);
}

void  FSDirectInputJoystickManager::addDevice(GUID guidDeviceInstance)
{
    if(_directInputToDeviceIDMap.find(guidDeviceInstance) == _directInputToDeviceIDMap.end())
    {
        LPDIRECTINPUTDEVICE8    _Joystick = NULL;

        _directInput8->CreateDevice(guidDeviceInstance,&_Joystick,NULL);
        unsigned int newID = this->getNextID();
        FSDirectInputJoystick * newJoystick = new FSDirectInputJoystick(_Joystick,newID,0,0,0,false,-1,-1);
        this->addDevice(newJoystick);
        _directInputToDeviceIDMap[guidDeviceInstance] = newID;
    }
}

void  FSDirectInputJoystickManager::removeDevice(GUID guidDeviceInstance)
{
    if(_directInputToDeviceIDMap.find(guidDeviceInstance) != _directInputToDeviceIDMap.end())
    {
     unsigned int id = _directInputToDeviceIDMap[guidDeviceInstance];
    const FSBaseDevice * joystickToDelete = this->getDevice(id);
     this->removeDevice((FSBaseDevice*)joystickToDelete);
    // _directInputToDeviceIDMap.erase(guidDeviceInstance);
    }
}

//-----------------------------------------------------------------------------
// Enum each PNP device using WMI and check each device ID to see if it contains
// "IG_" (ex. "VID_045E&PID_028E&IG_00").  If it does, then it's an XInput device
// Unfortunately this information can not be found by just using DirectInput
//-----------------------------------------------------------------------------
bool FSDirectInputJoystickManager::IsXInputDevice( const GUID* pGuidProductFromDirectInput )
{
    IWbemLocator*           pIWbemLocator  = NULL;
    IEnumWbemClassObject*   pEnumDevices   = NULL;
    IWbemClassObject*       pDevices[20]   = {0};
    IWbemServices*          pIWbemServices = NULL;
    BSTR                    bstrNamespace  = NULL;
    BSTR                    bstrDeviceID   = NULL;
    BSTR                    bstrClassName  = NULL;
    DWORD                   uReturned      = 0;
    bool                    bIsXinputDevice= false;
    UINT                    iDevice        = 0;
    VARIANT                 var;
    HRESULT                 hr;

    // CoInit if needed
    hr = CoInitialize(NULL);
    bool bCleanupCOM = SUCCEEDED(hr);

    // Create WMI
    hr = CoCreateInstance( __uuidof(WbemLocator),
                           NULL,
                           CLSCTX_INPROC_SERVER,
                           __uuidof(IWbemLocator),
                           (LPVOID*) &pIWbemLocator);
    if( FAILED(hr) || pIWbemLocator == NULL )
        goto LCleanup;

    bstrNamespace = SysAllocString( L"\\\\.\\root\\cimv2" );if( bstrNamespace == NULL ) goto LCleanup;
    bstrClassName = SysAllocString( L"Win32_PNPEntity" );   if( bstrClassName == NULL ) goto LCleanup;
    bstrDeviceID  = SysAllocString( L"DeviceID" );          if( bstrDeviceID == NULL )  goto LCleanup;

    // Connect to WMI
    hr = pIWbemLocator->ConnectServer( bstrNamespace, NULL, NULL, 0L,
                                       0L, NULL, NULL, &pIWbemServices );
    if( FAILED(hr) || pIWbemServices == NULL )
        goto LCleanup;

    // Switch security level to IMPERSONATE.
    CoSetProxyBlanket( pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
                       RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE );

    hr = pIWbemServices->CreateInstanceEnum( bstrClassName, 0, NULL, &pEnumDevices );
    if( FAILED(hr) || pEnumDevices == NULL )
        goto LCleanup;

    // Loop over all devices
    for( ;; )
    {
        // Get 20 at a time
        hr = pEnumDevices->Next( 10000, 20, pDevices, &uReturned );
        if( FAILED(hr) )
            goto LCleanup;
        if( uReturned == 0 )
            break;

        for( iDevice=0; iDevice<uReturned; iDevice++ )
        {
            // For each device, get its device ID
            hr = pDevices[iDevice]->Get( bstrDeviceID, 0L, &var, NULL, NULL );
            if( SUCCEEDED( hr ) && var.vt == VT_BSTR && var.bstrVal != NULL )
            {
                // Check if the device ID contains "IG_".  If it does, then it's an XInput device
                    // This information can not be found from DirectInput
                if( wcsstr( var.bstrVal, L"IG_" ) )
                {
                    // If it does, then get the VID/PID from var.bstrVal
                    DWORD dwPid = 0, dwVid = 0;
                    WCHAR* strVid = wcsstr( var.bstrVal, L"VID_" );
                    if( strVid && swscanf( strVid, L"VID_%4X", &dwVid ) != 1 )
                        dwVid = 0;
                    WCHAR* strPid = wcsstr( var.bstrVal, L"PID_" );
                    if( strPid && swscanf( strPid, L"PID_%4X", &dwPid ) != 1 )
                        dwPid = 0;

                    // Compare the VID/PID to the DInput device
                    DWORD dwVidPid = MAKELONG( dwVid, dwPid );
                    if( dwVidPid == pGuidProductFromDirectInput->Data1 )
                    {
                        bIsXinputDevice = true;
                        goto LCleanup;
                    }
                }
            }
            SAFE_RELEASE( pDevices[iDevice] );
        }
    }

LCleanup:
    if(bstrNamespace)
        SysFreeString(bstrNamespace);
    if(bstrDeviceID)
        SysFreeString(bstrDeviceID);
    if(bstrClassName)
        SysFreeString(bstrClassName);
    for( iDevice=0; iDevice<20; iDevice++ )
        SAFE_RELEASE( pDevices[iDevice] );
    SAFE_RELEASE( pEnumDevices );
    SAFE_RELEASE( pIWbemLocator );
    SAFE_RELEASE( pIWbemServices );

    if( bCleanupCOM )
        CoUninitialize();

    return bIsXinputDevice;
}
