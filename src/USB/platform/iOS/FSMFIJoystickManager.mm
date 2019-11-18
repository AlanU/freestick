#include "USB/platform/iOS/FSMFIJoystickManager.h"
#include "USB/platform/iOS/FSMFIJoystick.h"
#include "USB/common/FSUSBJoystickDeviceManager.h"
#include <array>
#import <GameController/GCController.h>
#import <Foundation/Foundation.h>
using namespace freestick;

FSMFIJoystickDeviceManager::FSMFIJoystickDeviceManager()
{

    // MFI controller

    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][A_BUTTON_MFI_EID] = ButtonA;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][B_BUTTON_MFI_EID] = ButtonB;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][X_BUTTON_MFI_EID] = ButtonX;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][Y_BUTTON_MFI_EID] = ButtonY;

    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_SHOULDER_BUTTON_MFI_EID] = LeftShoulder;//L1 sholder button
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_SHOULDER_BUTTON_MFI_EID] = RightShoulder;//R2 sholder button

    //xbox 360 is for 0 - 255 but xbox one is for 0 - 1023 and the xbox one driver pretends it is a xbox 360 with the 1023 value
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LTRIGGER_MFI_EID].push_back(FSUSBElementInfoMap(0,1,Trigger1,FSInputChanged));//L2 trigger
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RTRIGGER_MFI_EID].push_back(FSUSBElementInfoMap(0,1,Trigger2,FSInputChanged));//R2 trigger

    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_AXIS_BUTTON_MFI_EID] = Axis1Button;//L3 left thumb down
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_AXIS_BUTTON_MFI_EID] = Axis2Button;//R3 right thumb down

    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][MENU_BUTTON_MFI_EID] = ButtonSelect;//back

    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][UP_DPAD_MFI_EID] = DPadUp;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][DOWN_DPAD_MFI_EID] = DPadDown;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_DPAD_MFI_EID] = DPadLeft;
    _usageMapToInputEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_DPAD_MFI_EID] = DPadRight;

    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_XAXIS_MFI_EID].push_back(FSUSBElementInfoMap(-1,1,XAxis,FSInputChanged));//LXaxis stick trigger
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][LEFT_YAXIS_MFI_EID].push_back(FSUSBElementInfoMap(-1,1,YAxis,FSInputChanged));//LYaxis stick trigger

    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_XAXIS_MFI_EID].push_back(FSUSBElementInfoMap(-1,1,XAxis2,FSInputChanged));//RXaxis stick trigger
    _usageMapToInputRangeEvent[createVPId(APPLE_VENDER_ID,MFI_PRODUCT_ID)][RIGHT_YAXIS_MFI_EID].push_back(FSUSBElementInfoMap(-1,1,YAxis2,FSInputChanged));//RYaxis stick trigger


}

FSMFIJoystickDeviceManager::~FSMFIJoystickDeviceManager(){

}

void FSMFIJoystickDeviceManager::init() {
    FSUSBDeviceManager::init();
    NSLog(@"Init");
    /*[GCController startWirelessControllerDiscoveryWithCompletionHandler:^{
        updateControllers();
    }];
    [GCController stopWirelessControllerDiscovery];*/

    //Register for connections
   [[NSNotificationCenter defaultCenter] addObserverForName:GCControllerDidConnectNotification
                          object:nil
                          queue:nil
                          usingBlock:^(NSNotification * /*note*/)
                          {
                             updateConnectedControllers();
                            //updateControllers();
                          }
    ];

    [[NSNotificationCenter defaultCenter] addObserverForName:GCControllerDidDisconnectNotification
                           object:nil
                           queue:nil
                           usingBlock:^(NSNotification * /*note*/)
                           {
                             updateConnectedControllers();
                             //updateControllers();
                           }
     ];

}
//        void addMapping(vendorIDType vendorUSBID, productIDType productUSBID, idNumber controlUSBID,FSDeviceInput deviceInput);

void FSMFIJoystickDeviceManager::addMFIMapping()
{
        //TODO Map1 to the a button
    this->addMapping(APPLE_VENDER_ID,MFI_PRODUCT_ID,1,ButtonA);
}

void FSMFIJoystickDeviceManager::updateJoystickButtons(idNumber joyStickID,idNumber elementID, bool pressed,float value)
{
    //TODO get old value form elemement
    // TODO look up in map for FSDeviceInput
    FSEventAction buttonEvent = FSEventAction::FSInputRest;
    if(pressed)
    {
          if(value >= 1)
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
    //TODO get old value form elemement
    // TODO look up in map for FSDeviceInput


    auto map = lookUpDeviceInputFromUSBID(APPLE_VENDER_ID,MFI_PRODUCT_ID,elementID,elementID == LTRIGGER_MFI_EID || elementID == RTRIGGER_MFI_EID ? 0 :-1,1,value);
    inputOnDeviceChangedWithNormilzedValues(FreeStickEventType::FS_AXIS_EVENT
                                            ,FSEventAction::FSInputChanged
                                            ,map.getDeviceInput()
                                            ,joyStickID
                                            ,elementID,
                                            value,
                                           value );

}
void FSMFIJoystickDeviceManager::updateConnectedControllers(){

    ///TODO
    /// track what was last seen remove what is there
    /// what is left is what has been dissconnectd
    ///
    std::vector<mfiID> newThisUpdate;
    std::vector<mfiID> foundThisUpdate;
    unsigned int MFI_MAX_COUNT = 4;
    std::array<GCController*,4> lastState{nullptr,nullptr,nullptr,nullptr};

        for (unsigned int index = 0; index < MFI_MAX_COUNT; index++)
        {
                bool result = [GCController controllers].count > index;
                if(result)
                {
                    lastState[index] = [GCController controllers][index];
                    mfiID foundJoystick = index;
                    std::vector<mfiID>::iterator itr2 = std::find(_connectedLastUpdateJoysticks.begin(),
                                                                  _connectedLastUpdateJoysticks.end(),
                                                                   foundJoystick);
                    if (itr2 != _connectedLastUpdateJoysticks.end()) {
                        _connectedLastUpdateJoysticks.erase(itr2);

                    }else  {
                        newThisUpdate.push_back(foundJoystick);
                    }
                    foundThisUpdate.push_back(foundJoystick);
                }
        }
        for (int index =(int) _connectedLastUpdateJoysticks.size() - 1; index >= 0; index--) {
            mfiID deviceToDelete = _connectedLastUpdateJoysticks[index];
            this->removeMFIDevice(deviceToDelete );
        }
        std::vector<mfiID>::iterator itrAdd;
        for (itrAdd = newThisUpdate.begin(); itrAdd != newThisUpdate.end(); ++itrAdd) {
            this->addMFIDevice(*itrAdd,lastState[*itrAdd]);
        }

        _connectedLastUpdateJoysticks = foundThisUpdate;
}

void FSMFIJoystickDeviceManager::removeMFIDevice(mfiID device)
{
    if(_wordToIDControllerMap.find(device) != _wordToIDControllerMap.end())
    {
        elementID id = _wordToIDControllerMap[device];
        const FSBaseDevice * joystickToDelete = getDevice(id);
        removeDevice((FSBaseDevice*)joystickToDelete);
        _wordToIDControllerMap.erase(device);
    }
}

void FSMFIJoystickDeviceManager::addMFIDevice(mfiID device, void * controller)
{
    if(_wordToIDControllerMap.find(device) == _wordToIDControllerMap.end())
    {
       unsigned int newId = getNextID();
       _wordToIDControllerMap[device] = newId;

        unsigned int numberOfButtons = 5;
        unsigned int numberOfAnlogSticks =2;
        unsigned int numberOfDigitalSticks=1;
        bool  forceFeedBackSupported =false;
        vendorIDType vendorID = 0;
        productIDType productID = 0;
       // controller.playerIndex = static_cast<GCControllerPlayerIndex>(contorllerCount++);

        FSUSBDeviceManager::addDevice(new FSMFIJoystick(static_cast<void *>(controller),
                                                        newId,
                                                        numberOfButtons,
                                                        numberOfAnlogSticks,
                                                        numberOfDigitalSticks,
                                                        forceFeedBackSupported,
                                                        vendorID,
                                                        productID));

    }

}


void FSMFIJoystickDeviceManager::updateControllers(){
    // Remove old controlers
    //This is the inital update uses GCControllerDIdConnectNotifcation for add and
    // GSControllerDidDisconnectNotification
    NSInteger contorllerCount = 0;
    for(GCController * controller in [GCController controllers] ){
        // TODO create FSMFIJoystick
        NSLog(@"vender Name %@",[controller vendorName]);
        idNumber joyStickID = [controller playerIndex];
        unsigned int numberOfButtons = 5;
        unsigned int numberOfAnlogSticks =2;
        unsigned int numberOfDigitalSticks=1;
        bool  forceFeedBackSupported =false;
        vendorIDType vendorID = 0;
        productIDType productID = 0;
        controller.playerIndex = static_cast<GCControllerPlayerIndex>(contorllerCount++);

        FSUSBDeviceManager::addDevice(new FSMFIJoystick(static_cast<void *>(controller),
                                                         joyStickID,
                                                        numberOfButtons,
                                                        numberOfAnlogSticks,
                                                        numberOfDigitalSticks,
                                                        forceFeedBackSupported,
                                                        vendorID,
                                                        productID));
        if([controller extendedGamepad])
        {
            [controller extendedGamepad].buttonA.valueChangedHandler = ^(GCControllerButtonInput * button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,A_BUTTON_MFI_EID,pressed,value); };
            [controller extendedGamepad].buttonB.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,B_BUTTON_MFI_EID,pressed,value); };
            [controller extendedGamepad].buttonX.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,X_BUTTON_MFI_EID,pressed,value); };
            [controller extendedGamepad].buttonY.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,Y_BUTTON_MFI_EID,pressed,value); };
            [controller extendedGamepad].buttonMenu.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,MENU_BUTTON_MFI_EID,pressed,value); };
            [controller extendedGamepad].dpad.up.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,UP_DPAD_MFI_EID,pressed,value); };
            [controller extendedGamepad].dpad.down.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,DOWN_DPAD_MFI_EID,pressed,value); };
            [controller extendedGamepad].dpad.left.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,LEFT_DPAD_MFI_EID,pressed,value); };
            [controller extendedGamepad].dpad.right.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,RIGHT_DPAD_MFI_EID,pressed,value); };
            [controller extendedGamepad].leftShoulder.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,LEFT_SHOULDER_BUTTON_MFI_EID,pressed,value); };
            [controller extendedGamepad].rightShoulder.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,RIGHT_SHOULDER_BUTTON_MFI_EID,pressed,value); };

            [controller extendedGamepad].leftTrigger.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickAnalog(joyStickID,LTRIGGER_MFI_EID,value); };
            [controller extendedGamepad].rightTrigger.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickAnalog(joyStickID,RTRIGGER_MFI_EID,value); };

            [controller extendedGamepad].leftThumbstick.xAxis.valueChangedHandler = ^(GCControllerAxisInput *axis,float value)
            { updateJoystickAnalog(joyStickID,LEFT_XAXIS_MFI_EID,value); };
            [controller extendedGamepad].leftThumbstick.yAxis.valueChangedHandler = ^(GCControllerAxisInput *axis,float value)
            { updateJoystickAnalog(joyStickID,LEFT_YAXIS_MFI_EID,value); };

            [controller extendedGamepad].rightThumbstick.xAxis.valueChangedHandler = ^(GCControllerAxisInput *axis,float value)
            { updateJoystickAnalog(joyStickID,RIGHT_XAXIS_MFI_EID,value); };
            [controller extendedGamepad].rightThumbstick.yAxis.valueChangedHandler = ^(GCControllerAxisInput *axis,float value)
            { updateJoystickAnalog(joyStickID,RIGHT_YAXIS_MFI_EID,value); };

            //Add check for IOS
            if (@available(iOS 12.1, *)) {
                [controller extendedGamepad].leftThumbstickButton.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,LTRIGGER_MFI_EID,pressed,value); };
            [controller extendedGamepad].rightThumbstickButton.valueChangedHandler = ^(GCControllerButtonInput *button,float value, BOOL pressed)
            { updateJoystickButtons(joyStickID,RTRIGGER_MFI_EID,pressed,value); };
            }

        }
        else if([controller microGamepad])
        {

        }
    }
}

