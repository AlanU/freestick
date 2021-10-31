//#ifdef __OBJC__
/*#import <GameController/GCController.h>
//#import <GameController/GCUtility.h>
@class _GCCControllerHIDServiceInfo;

@interface GCController ()
+ (void)__openXPC_and_CBApplicationDidBecomeActive__;
@property (nonatomic, retain, readonly) NSArray<_GCCControllerHIDServiceInfo *> *hidServices;
@end


typedef struct CF_BRIDGED_TYPE(id) __IOHIDServiceClient * IOHIDServiceClientRef;
Class ControllerClassForService(IOHIDServiceClientRef);


@interface _GCCControllerHIDServiceInfo : NSObject
@property (nonatomic, readonly) IOHIDServiceClientRef service;
@end
//#endif*/
#import <GameController/GCController.h>
#import <IOKit/hidsystem/IOHIDEventSystemClient.h>
typedef struct __IOHIDServiceClient* IOHIDServiceClientRef;
@interface _GCCControllerHIDServiceInfo : NSObject
@property (nonatomic, readonly) IOHIDServiceClientRef service;
@end

@class _GCCControllerHIDServiceInfo;
@interface GCController ()
+ (void)__openXPC_and_CBApplicationDidBecomeActive__;
@property (nonatomic, retain, readonly) NSArray<_GCCControllerHIDServiceInfo *> *hidServices;
@property (nonatomic, retain, readonly) NSString * identifier;
@end



