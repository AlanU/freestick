#include "USB/platform/iOS/FSMFIJoystick.h"
#include <sstream>
#import <GameController/GCController.h>
#import <CoreHaptics/CHHapticEngine.h>
#import <GameController/GCDeviceHaptics.h>
#import <CoreHaptics/CHHapticPattern.h>
#import <Foundation/Foundation.h>
#if  ! __has_feature(objc_arc)
    #error This file must be compiled with ARC. Use -fobjc-arc flag (or convert project to ARC).
#endif

NSDictionary* gethapticDict(){
static NSDictionary* hapticDict = nil;
#if TARGET_OS_IPHONE
if (@available(iOS 13, *) )
#elif TARGET_OS_TV
if (@available(tvOS 14.0, *) )
#else
if (@available(macOS 10.15, *))
#endif
{
hapticDict =
@{
 CHHapticPatternKeyPattern:
       @[ // Start of array
         @{  // Start of first dictionary entry in the array
             CHHapticPatternKeyEvent: @{ // Start of first item
                     CHHapticPatternKeyEventType:CHHapticEventTypeHapticContinuous,
                     CHHapticPatternKeyTime:@0.010f,
                     CHHapticPatternKeyEventDuration:@2.0,
                     CHHapticPatternKeyEventParameters: @[
                        @{ @"ParameterID": @"HapticIntensity", @"ParameterValue":@0.9852941176470589},
                        @{ @"ParameterID": @"HapticSharpness", @"ParameterValue":@0.9852941176470589}
                     ]
                     },  // End of first item
           }, // End of first dictionary entry in the array
        ], // End of array
 };
}
return hapticDict;

}

class EngineWrapper
{
public:
    EngineWrapper(CHHapticEngine * newEngine):engine(newEngine){}
    ~EngineWrapper(){ engine= nullptr;}
    CHHapticEngine * getEngine()
    {
        return engine;
    }
private:

    CHHapticEngine * engine;
};


using namespace freestick;

FSMFIJoystick::FSMFIJoystick()
{

}

FSMFIJoystick::~FSMFIJoystick()
{
    if(hapticEngineWrapper)
    {
        delete hapticEngineWrapper;
    }
}

FSMFIJoystick::FSMFIJoystick(const void * controller,idNumber joyStickID,
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
    addMFIElements(controller);
    GCController * gccontroller = static_cast<GCController*>(CFBridgingRelease(controller));
    controller = nullptr;
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

void FSMFIJoystick::addMFIElements(const void * controller)
{
    GCController * gccontroller = static_cast<GCController*>(CFBridgingRelease(controller));
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
#if TARGET_OS_IPHONE
if (@available(iOS 12.1, *) )
#elif TARGET_OS_TV
if (@available(tvOS 12.1, *) )
#else
if (@available(macOS 10.14.1, *))
#endif
{
    if([gccontroller extendedGamepad].leftThumbstickButton != nil)
    {
        addButtonElement(LEFT_AXIS_BUTTON_MFI_EID);
        _hasL3Button = true;
    }
    if([gccontroller extendedGamepad].rightThumbstickButton != nil)
    {
        addButtonElement(RIGHT_AXIS_BUTTON_MFI_EID);
        _hasR3Button = true;
    }
}
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

void FSMFIJoystick::createEngine(const void * contollerToCreateEngine){
    #if TARGET_OS_IPHONE
    if (@available(iOS 13, *) )
    #elif TARGET_OS_TV
    if (@available(tvOS 14.0, *) )
    #else
    if (@available(macOS 11.0, *))
    #endif
    {
        if(hapticEngineWrapper == nullptr && getForceFeedbackSupport())
        {
            GCController * controller = static_cast<GCController*>(CFBridgingRelease(contollerToCreateEngine));
            CHHapticEngine * engine = [controller.haptics createEngineWithLocality:GCHapticsLocalityDefault];
            hapticEngineWrapper = new EngineWrapper(engine);
        }
    }
}

void FSMFIJoystick::vibrate() const
{
    if(hapticEngineWrapper)
    {
        CHHapticEngine * engine = hapticEngineWrapper->getEngine();
        [engine startAndReturnError:nil];
        NSError * error = nil;
        CHHapticPattern* pattern = [[CHHapticPattern alloc] initWithDictionary:gethapticDict() error:&error];
        if(error)
            return;
        error = nil;
        id<CHHapticPatternPlayer> hapticPlayer = [engine createPlayerWithPattern:pattern error:&error];
        if(error)
           return;
        [hapticPlayer startAtTime:0.0f error:&error];
    }
}






