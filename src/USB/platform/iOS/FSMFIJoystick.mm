#include "USB/platform/iOS/FSMFIJoystick.h"
#include <sstream>
#import <GameController/GCController.h>
#import <Foundation/Foundation.h>
using namespace freestick;
FSMFIJoystick::FSMFIJoystick()
{

}

FSMFIJoystick::FSMFIJoystick(void * controller,idNumber joyStickID,
              unsigned int numberOfButtons,
              unsigned int numberOfAnlogSticks,
              unsigned int numberOfDigitalSticks,
              bool  forceFeedBackSupported,
              vendorIDType vendorID,
              productIDType productID):
              FSUSBJoystick(joyStickID,
                            numberOfButtons,
                            numberOfAnlogSticks,
                            numberOfDigitalSticks,
                            forceFeedBackSupported,
                            vendorID,
                            productID)
{
    GCController * gccontroller = static_cast<GCController*>(controller);

    std::stringstream playerNumber;
    playerNumber << joyStickID;
    addMFIElements();
    _vendorIDFriendlyName = [[gccontroller vendorName] UTF8String];
    #if TARGET_OS_IPHONE
    if (@available(iOS 13.0, *) )
    #elif TARGET_OS_TV
    if (@available(tvOS 13.0, *) )
    #else
    if (@available(macOS 10.15, *))
    #endif
    {
        _productIDFriendlyName = [[gccontroller productCategory]UTF8String];
        _productIDFriendlyName += " Player " + playerNumber.str();
    } else {
        // Fallback on earlier versions
        _productIDFriendlyName = "Player " + playerNumber.str();
    }
    _friendlyName = _vendorIDFriendlyName + " "+ _productIDFriendlyName;
   // _friendlyName = [[gccontroller vendorName] UTF8String];
}

bool FSMFIJoystick::setElementValue(elementID element,float value)
{
    for (auto &itr : _inputElementMap)
    {
        if (itr.first == element)
        {
            (itr.second).setValue(value);
            return true;
        }
    }
    return false;
}

void FSMFIJoystick::addMFIElements()
{
    addButtonElement(UP_DPAD_MFI_EID);
    addButtonElement(DOWN_DPAD_MFI_EID);
    addButtonElement(LEFT_DPAD_MFI_EID);
    addButtonElement(RIGHT_DPAD_MFI_EID);

    addButtonElement(A_BUTTON_MFI_EID);
    addButtonElement(B_BUTTON_MFI_EID);
    addButtonElement(X_BUTTON_MFI_EID);
    addButtonElement(Y_BUTTON_MFI_EID);

    addButtonElement(MENU_BUTTON_MFI_EID);

    addButtonElement(LEFT_SHOULDER_BUTTON_MFI_EID);
    addButtonElement(RIGHT_SHOULDER_BUTTON_MFI_EID);


    addButtonElement(LEFT_AXIS_BUTTON_MFI_EID);
    addButtonElement(RIGHT_AXIS_BUTTON_MFI_EID);


    addElement(LEFT_XAXIS_MFI_EID,-1,1,0);
    addElement(LEFT_YAXIS_MFI_EID,-1,1,0);

    addElement(RIGHT_XAXIS_MFI_EID,-1,1,0);
    addElement(RIGHT_YAXIS_MFI_EID,-1,1,0);

    addElement(LTRIGGER_MFI_EID,-1,1,0);
    addElement(RTRIGGER_MFI_EID,-1,1,0);


}

void FSMFIJoystick::addButtonElement(unsigned int buttonID)
{

   addElement(buttonID,0,1,0);
}

void FSMFIJoystick::addElement(unsigned int buttonID,minMaxNumber min,minMaxNumber max,physicalValueNumber currentValue)
{
    FSUSBJoyStickInputElement newElement (buttonID,
                                          getJoystickID() ,
                                          min,
                                          max,
                                          APPLE_VENDER_ID,
                                          MFI_PRODUCT_ID,
                                          nullptr,
                                          currentValue,
                                          ++_totalButtonNumber);
    if(min == 0)
    {
        newElement.setValue(0); //since all buttons are pressure sensitive they need to be initlized to zero for manager to fire events correctly
    }
    this->addInputElement(newElement);

}






