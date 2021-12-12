#include "USB/platform/iOS/FSMFIJoystickManager.h"
#include "USB/platform/iOS/FSMFIJoystick.h"
#include "USB/common/FSUSBJoystickDeviceManager.h"
#include <array>
#import <GameController/GCController.h>
#import <Foundation/Foundation.h>
using namespace freestick;

#if TARGET_OS_OSX
#include "USB/platform/MacOSX/FSMacUtil.h"
#import "USB/platform/MacOSX/GCController+hidServices.h"
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/hid/IOHIDLib.h>
#include <IOKit/IOKitLib.h>
typedef struct CF_BRIDGED_TYPE(id) __IOHIDServiceClient * IOHIDServiceClientRef;
extern "C" CFTypeRef _Nullable IOHIDServiceClientCopyProperty(IOHIDServiceClientRef service, CFStringRef key);
#endif
const int valueMultiplier = 10000000;
FSMFIJoystickDeviceManager::FSMFIJoystickDeviceManager()
{

    // MFI controller

    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][A_BUTTON_MFI_EID] = ButtonA;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][B_BUTTON_MFI_EID] = ButtonB;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][X_BUTTON_MFI_EID] = ButtonX;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][Y_BUTTON_MFI_EID] = ButtonY;

    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_SHOULDER_BUTTON_MFI_EID] = LeftShoulder;//L1 sholder button
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_SHOULDER_BUTTON_MFI_EID] = RightShoulder;//R2 sholder button

    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LTRIGGER_MFI_EID].push_back(FSUSBElementInfoMap(0,1,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RTRIGGER_MFI_EID].push_back(FSUSBElementInfoMap(0,1,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LTRIGGER_MFI_EID].push_back(FSUSBElementInfoMap(0,valueMultiplier,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RTRIGGER_MFI_EID].push_back(FSUSBElementInfoMap(0,valueMultiplier,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_AXIS_BUTTON_MFI_EID] = Axis1Button;//L3 left thumb down
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_AXIS_BUTTON_MFI_EID] = Axis2Button;//R3 right thumb down

    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][MENU_BUTTON_MFI_EID] = ButtonSelect;//back

    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][UP_DPAD_MFI_EID] = DPadUp;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][DOWN_DPAD_MFI_EID] = DPadDown;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_DPAD_MFI_EID] = DPadLeft;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_DPAD_MFI_EID] = DPadRight;

    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_XAXIS_MFI_EID].push_back(FSUSBElementInfoMap(-1,1,XAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_YAXIS_MFI_EID].push_back(FSUSBElementInfoMap(-1,1,YAxis,FSInputChanged));//LYaxis stick trigger
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_XAXIS_MFI_EID].push_back(FSUSBElementInfoMap(valueMultiplier*-1,valueMultiplier,XAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_YAXIS_MFI_EID].push_back(FSUSBElementInfoMap(valueMultiplier*-1,valueMultiplier,YAxis,FSInputChanged));//LXaxis stick trigger

    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_XAXIS_MFI_EID].push_back(FSUSBElementInfoMap(-1,1,XAxis2,FSInputChanged));//RXaxis stick trigger
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_YAXIS_MFI_EID].push_back(FSUSBElementInfoMap(-1,1,YAxis2,FSInputChanged));//RYaxis stick trigger
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_XAXIS_MFI_EID].push_back(FSUSBElementInfoMap(valueMultiplier*-1,valueMultiplier,XAxis2,FSInputChanged));//RXaxis stick trigger
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_YAXIS_MFI_EID].push_back(FSUSBElementInfoMap(valueMultiplier*-1,valueMultiplier,YAxis2,FSInputChanged));//RYaxis stick trigger

}

FSMFIJoystickDeviceManager::~FSMFIJoystickDeviceManager(){

}

void FSMFIJoystickDeviceManager::init() {
    FSUSBDeviceManager::init();
    //Register for connections
   [[NSNotificationCenter defaultCenter] addObserverForName:GCControllerDidConnectNotification
                          object:nil
                          queue:nil
                          usingBlock:^(NSNotification * note)
                          {
                            addMFIDevice(static_cast<void *>(note.object));
                          }
    ];

    [[NSNotificationCenter defaultCenter] addObserverForName:GCControllerDidDisconnectNotification
                           object:nil
                           queue:nil
                           usingBlock:^(NSNotification * note)
                           {
                             removeMFIDevice(static_cast<void *>(note.object));\
                           }
     ];

}

void FSMFIJoystickDeviceManager::removeMFIDevice(void * device)
{
    if(_wordToIDControllerMap.find(device) != _wordToIDControllerMap.end())
    {
        elementID id = _wordToIDControllerMap[device];
        const FSBaseDevice * joystickToDelete = getDevice(id);
        removeDevice(const_cast<FSBaseDevice*>(joystickToDelete));
        _wordToIDControllerMap.erase(device);
    }
}

void FSMFIJoystickDeviceManager::addMFIDevice(void * device)
{
    GCController * controller = static_cast<GCController * >(device);
    if([controller extendedGamepad] && _wordToIDControllerMap.find(device) == _wordToIDControllerMap.end())
    {
       unsigned int newId = getNextID();
       _wordToIDControllerMap[device] = newId;

        unsigned int numberOfButtons = 5;
        unsigned int numberOfAnlogSticks =2;
        unsigned int numberOfDigitalSticks=1;
        bool  forceFeedbackSupported =false;
        #if TARGET_OS_OSX
        if(@available(macOS 11, *))
        #elif TARGET_OS_IOS
        if(@available(iOS 14, *))
        #elif TARGET_OS_TV
        if(@available(tvOS 14, *))
        #endif
        {
          forceFeedbackSupported = [controller haptics] != nil;
        }
        uint16_t vendorID = APPLE_VENDER_ID;
        uint16_t productID = MFI_PRODUCT_ID;
       // controller.playerIndex = static_cast<GCControllerPlayerIndex>(contorllerCount++);

#if TARGET_OS_OSX
        GCController * gccontroller = static_cast<GCController*>(device);
        if(@available(macOS 11, *))
        {
            auto vpId = getVendorAndProductFromUniqueID([[gccontroller identifier] UTF8String]);
            if(vpId.first)
            {
                FSUSBJoystickDeviceManager::getUsageFromIdForElement(vpId.second,vendorID,productID);
                removeDeviceFromManagers(vendorID,productID);
            }
        }
        else if(@available(macOS 10.9, *))
        {
            for (_GCCControllerHIDServiceInfo *serviceInfo in controller.hidServices) {
                if (serviceInfo.service)
                {
                        int vendorInt = 0 ;
                        int productInt = 0;
                        CFNumberRef vendor = static_cast<CFNumberRef>(IOHIDServiceClientCopyProperty(serviceInfo.service, CFSTR(kIOHIDVendorIDKey)));
                        if (vendor)
                        {
                            CFNumberGetValue(vendor, kCFNumberSInt32Type, &vendorInt);
                            vendorID = vendorInt;
                            CFRelease(vendor);
                        }

                        CFNumberRef product = static_cast<CFNumberRef>(IOHIDServiceClientCopyProperty(serviceInfo.service, CFSTR(kIOHIDProductIDKey)));
                        if (product)
                        {
                            CFNumberGetValue(product, kCFNumberSInt32Type, &productInt);
                            productID = productInt;
                            CFRelease(product);
                        }
                        removeDeviceFromManagers(vendorID,productID);
                }
            }
        }
#endif
        FSUSBDeviceManager::addDevice(new FSMFIJoystick(device,
                                                        newId,
                                                        numberOfButtons,
                                                        numberOfAnlogSticks,
                                                        numberOfDigitalSticks,
                                                        forceFeedbackSupported,
                                                        vendorID,
                                                        productID));

        connectControlesToController(device,newId);

    }

}


void FSMFIJoystickDeviceManager::updateJoystickButtons(idNumber joyStickID,idNumber elementID, bool pressed,float value)
{
    //TODO create new templated USBJoystick to support FSUSBNormlizedJoyStickInputElement
    FSMFIJoystick * contorller = nullptr;
    if(deviceMap.find(joyStickID) != deviceMap.end())
    {
         contorller = static_cast<FSMFIJoystick *>(deviceMap[joyStickID]);
    }
    if(contorller)
    {
        contorller->setElementValue(elementID,value*valueMultiplier);
    }
    FSEventAction buttonEvent = FSEventAction::FSInputRest;
    if(pressed)
    {
          auto element = contorller->findInputElement(elementID);
          if(element && element->getOldValue() == 0)
          {
             buttonEvent =  FSEventAction::FSInputPressed;
          }
          else
          {
             buttonEvent =  FSEventAction::FSInputChanged;
          }
    }

    auto map = _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][elementID];
    inputOnDeviceChangedWithNormilzedValues(FreeStickEventType::FS_BUTTON_EVENT
                                            ,buttonEvent
                                            ,map
                                            ,joyStickID
                                            ,elementID,
                                            value,
                                           value );

}

void FSMFIJoystickDeviceManager::updateJoystickAnalog(idNumber joyStickID,idNumber elementID,float value)
{
    FSMFIJoystick * contorller = nullptr;
    if(deviceMap.find(joyStickID) != deviceMap.end())
    {
         contorller = static_cast<FSMFIJoystick *>(deviceMap[joyStickID]);
    }
    if(contorller)
    {
        contorller->setElementValue(elementID,value*valueMultiplier);
    }
    bool forceAnalog = elementID == LTRIGGER_MFI_EID || elementID == RTRIGGER_MFI_EID;
    //TODO get old value form elemement
    auto map = lookUpDeviceInputFromUSBID(APPLE_VENDER_ID,MFI_PRODUCT_ID,elementID,forceAnalog ? 0 :-1,1,value,forceAnalog);
    inputOnDeviceChangedWithNormilzedValues(FreeStickEventType::FS_AXIS_EVENT
                                            ,FSEventAction::FSInputChanged
                                            ,map.getDeviceInput()
                                            ,joyStickID
                                            ,elementID
                                            ,value
                                            ,value
                                            );

}

void FSMFIJoystickDeviceManager::connectControlesToController(void * contorllerToConnect,idNumber joyStickID )
{
    #if TARGET_OS_IPHONE
    if (@available(iOS 7.0, *) )
    #elif TARGET_OS_TV
    if (@available(tvOS 9.0, *) )
    #else
    if (@available(macOS 10.9, *))
    #endif
    {
    GCController * controller = static_cast<GCController*>(contorllerToConnect);
        if([controller extendedGamepad])
        {
            [controller extendedGamepad].buttonA.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,A_BUTTON_MFI_EID,pressed,value); };
            [controller extendedGamepad].buttonB.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,B_BUTTON_MFI_EID,pressed,value); };
            [controller extendedGamepad].buttonX.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,X_BUTTON_MFI_EID,pressed,value); };

            [controller extendedGamepad].buttonY.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,Y_BUTTON_MFI_EID,pressed,value); };
            #if TARGET_OS_IPHONE
            if (@available(iOS 13.0, *) )
            #elif TARGET_OS_TV
            if (@available(tvOS 13.0, *) )
            #else
            if (@available(macOS 10.15, *))
            #endif
            {
                [controller extendedGamepad].buttonMenu.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
                { updateJoystickButtons(joyStickID,MENU_BUTTON_MFI_EID,pressed,value); };
            }
            [controller extendedGamepad].dpad.up.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,UP_DPAD_MFI_EID,pressed,value); };
            [controller extendedGamepad].dpad.down.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,DOWN_DPAD_MFI_EID,pressed,value); };
            [controller extendedGamepad].dpad.left.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,LEFT_DPAD_MFI_EID,pressed,value); };
            [controller extendedGamepad].dpad.right.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,RIGHT_DPAD_MFI_EID,pressed,value); };

            [controller extendedGamepad].leftShoulder.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,LEFT_SHOULDER_BUTTON_MFI_EID,pressed,value); };
            [controller extendedGamepad].rightShoulder.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,RIGHT_SHOULDER_BUTTON_MFI_EID,pressed,value); };

            [controller extendedGamepad].leftTrigger.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL /*pressed*/)
            {     updateJoystickAnalog(joyStickID,LTRIGGER_MFI_EID,value); };
            [controller extendedGamepad].rightTrigger.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL /*pressed*/)
            { updateJoystickAnalog(joyStickID,RTRIGGER_MFI_EID,value);};

            [controller extendedGamepad].leftThumbstick.xAxis.valueChangedHandler = ^(GCControllerAxisInput * /*axis*/,float value)
            { updateJoystickAnalog(joyStickID,LEFT_XAXIS_MFI_EID,value); };
            [controller extendedGamepad].leftThumbstick.yAxis.valueChangedHandler = ^(GCControllerAxisInput */*axis*/,float value)
            { updateJoystickAnalog(joyStickID,LEFT_YAXIS_MFI_EID,value*-1); };

            [controller extendedGamepad].rightThumbstick.xAxis.valueChangedHandler = ^(GCControllerAxisInput */*axis*/,float value)
            { updateJoystickAnalog(joyStickID,RIGHT_XAXIS_MFI_EID,value); };
            [controller extendedGamepad].rightThumbstick.yAxis.valueChangedHandler = ^(GCControllerAxisInput */*axis*/,float value)
            { updateJoystickAnalog(joyStickID,RIGHT_YAXIS_MFI_EID,value*-1); };



            //Add check for IOS
            #if TARGET_OS_IPHONE
            if (@available(iOS 12.1, *) )
            #elif TARGET_OS_TV
            if (@available(tvOS 12.1, *) )
            #else
            if (@available(macOS 10.14.1, *))
            #endif
            {
              [controller extendedGamepad].leftThumbstickButton.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
              { updateJoystickButtons(joyStickID,LEFT_AXIS_BUTTON_MFI_EID,pressed,value); };

              [controller extendedGamepad].rightThumbstickButton.valueChangedHandler = ^(GCControllerButtonInput * /*button*/,float value, BOOL pressed)
              { updateJoystickButtons(joyStickID,RIGHT_AXIS_BUTTON_MFI_EID,pressed,value); };
            }

        }
        else if([controller microGamepad])
        {
            // TODO add support
        }
    }
}



FSUSBElementInfoMap FSMFIJoystickDeviceManager::lookUpDeviceInputFromUSBID( vendorIDType vendorUSBID, productIDType productUSBID , unsigned int controlID,minMaxNumber min,minMaxNumber max,int value,bool forceAnalogLookup)
{
    return FSUpdatableJoystickDeviceManager::lookUpDeviceInputFromUSBID(APPLE_VENDER_ID,MFI_PRODUCT_ID, controlID,min,max,value,forceAnalogLookup);
}

bool FSMFIJoystickDeviceManager::doesDeviceHaveDeviceInput(vendorIDType vendorUSBID, productIDType productUSBID ,FSDeviceInput inputToLookFor)
{
    return FSUpdatableJoystickDeviceManager::doesDeviceHaveDeviceInput(APPLE_VENDER_ID, MFI_PRODUCT_ID, inputToLookFor);
}

bool FSMFIJoystickDeviceManager::doesDeviceHaveDeviceInputForValue(vendorIDType vendorUSBID, productIDType productUSBID ,FSDeviceInput inputToLookFor,physicalValueNumber value )
{
   return FSUpdatableJoystickDeviceManager::doesDeviceHaveDeviceInputForValue(APPLE_VENDER_ID, MFI_PRODUCT_ID, inputToLookFor, value );
}

bool FSMFIJoystickDeviceManager::doesDeviceHaveDeviceInput(idNumber deviceID,FSDeviceInput inputToLookFor)
{
    if(inputToLookFor == FSDeviceInput::Axis1Button || inputToLookFor == FSDeviceInput::Axis2Button )
    {
       bool hasInput = false;
       auto device =  getDevice(deviceID);
       if(device && device->getClassType() == FSMFIJoystickType)
       {
           auto mfiDevice = static_cast<const FSMFIJoystick *>(device);
           hasInput = inputToLookFor == FSDeviceInput::Axis1Button ? mfiDevice->hasL3Button() : mfiDevice->hasR3Button();
       }
       return hasInput;
    }
    else
    {
       return  FSUpdatableJoystickDeviceManager::doesDeviceHaveDeviceInput(deviceID,inputToLookFor);
    }
}

