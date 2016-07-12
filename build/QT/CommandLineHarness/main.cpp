#include "freestick.h"
#include "3rdParty/EELog/src/EELog.h"
#include <thread>
#include <chrono>
using namespace freestick;
class JoystickEventHandler: public IFSJoystickListener
   {
      public:
          JoystickEventHandler(){};
          ~JoystickEventHandler(){};
          virtual void onButtonDown(freestick::FSDeviceInputEvent event)
          {
              EE_INFO<<"ButtonDown "<<std::endl;
          }
          virtual void onButtonUp(freestick::FSDeviceInputEvent event)
          {
              EE_INFO<<"ButtonUp "<<std::endl;

          }
          virtual void onStickMove(freestick::FSDeviceInputEvent event)
          {
              EE_INFO<<"OnStickMove"<<std::endl;
          }
          virtual void onDisconnect(freestick::FSBaseEvent event)
          {
              EE_INFO<<"OnDisconnect"<<std::endl;

          }
          virtual void onConnect(freestick::FSBaseEvent event)
          {
              EE_INFO<<"OnConnect"<<std::endl;
          }
   };
int main(int argc, char *argv[])
{
    JoystickEventHandler handler;
    FreeStickDeviceManager deviceManager;

    deviceManager.init();
    deviceManager.ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                            FS_JOYSTICK_DISCONNECT_EVENT |
                                                            FS_BUTTON_EVENT | FS_AXIS_EVENT |
                                                            FS_TRIGGER_EVENT , handler);
    char command = ' ';
    while(true)
    {
        deviceManager.update();
    }
    return 0;
}
