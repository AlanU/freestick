#include "USB/platform/Windows/FSWindowsJoystickDeviceManager.h"

#define LOOP_OVER_MANAGERS_WITH_FUNCTION(func) for(unique_ptr_of_managers & manager : managers) { manager->func; }
#define Does_Have_Device_Input(func)  bool result = false;   for(unique_ptr_of_managers & manager : managers) {if(manager->func) {result = true; break;}} return result;
using namespace freestick;
FSWindowsJoystickDeviceManager::FSWindowsJoystickDeviceManager()
{
   managers.reserve(2);
   managers.push_back(unique_ptr_of_managers (new FSDirectInputJoystickManager));
   managers.push_back(unique_ptr_of_managers (new FSXInputJoystickDeviceManager));
}

FSWindowsJoystickDeviceManager::~FSWindowsJoystickDeviceManager()
{
    managers.clear();
}

void FSWindowsJoystickDeviceManager::ListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener)
{
     LOOP_OVER_MANAGERS_WITH_FUNCTION(ListenForAllJoysticksForEventTypes(eventFlags , listener))
}

void FSWindowsJoystickDeviceManager::UnListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener)
{

    LOOP_OVER_MANAGERS_WITH_FUNCTION( UnListenForAllJoysticksForEventTypes(eventFlags,listener))
}


void FSWindowsJoystickDeviceManager::init( )
{
    for(unique_ptr_of_managers & manager : managers)
    {
        static_cast<FSBaseManager*>(manager.get())->init(this);
    }
}

void FSWindowsJoystickDeviceManager::update()
{
    LOOP_OVER_MANAGERS_WITH_FUNCTION(update())
}

const FSBaseDevice * FSWindowsJoystickDeviceManager::getDevice(ElementID deviceID)
{
    //This is still faster then calling findManagerForDevice until the std::maps are changer to unordered_map
     const FSBaseDevice * device = nullptr;
     for(unique_ptr_of_managers & manager : managers)
     {
         device =  manager->getDevice(deviceID);
         if(device != nullptr)
         {
             break;
         }
     }
    return device;
}

managerType * FSWindowsJoystickDeviceManager::findManagerForDevice(ElementID deviceID)
{
    managerType * resultManger = nullptr;
    for(unique_ptr_of_managers & manager : managers)
    {
        const FSBaseDevice * device =  manager->getDevice(deviceID);
        if(device != nullptr)
        {
            resultManger = manager.get();
            break;
        }
    }
   return resultManger;
}

ElementID FSWindowsJoystickDeviceManager::getNextID()
{
    static unsigned int ID = 1;//0 is reserved for errors
    return (ID++);
}

/*void FSWindowsJoystickDeviceManager::addMappingForButton(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput)
{
    LOOP_OVER_MANAGERS_WITH_FUNCTION(addMappingForButton(vendorUSBID, productUSBID, controlUSBID, deviceInput));
}*/

void FSWindowsJoystickDeviceManager::addMapping(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput)
{
     LOOP_OVER_MANAGERS_WITH_FUNCTION(addMapping(vendorUSBID, productUSBID, controlUSBID, deviceInput));
}

void FSWindowsJoystickDeviceManager::addMapping(unsigned int deviceID,unsigned int controlID,FSDeviceInput deviceInput)
{
     LOOP_OVER_MANAGERS_WITH_FUNCTION(addMapping(deviceID,controlID, deviceInput));
}

FSUSBElementInfoMap FSWindowsJoystickDeviceManager::lookUpDeviceInputFromID(unsigned int deviceID, unsigned int controlID, MinMaxNumber min, MinMaxNumber max,int value)
{
    managerType * managerForDevice = findManagerForDevice(deviceID);
    if(managerForDevice != nullptr)
    {
        return managerForDevice->lookUpDeviceInputFromID(deviceID, controlID, min, max, value);
    }
    return FSUSBElementInfoMap(0,1,LastInput,FSInputChanged);
}

FSUSBElementInfoMap FSWindowsJoystickDeviceManager::lookUpDeviceInputFromUSBID( unsigned int vendorUSBID, unsigned int productUSBID , unsigned int controlID,MinMaxNumber min,MinMaxNumber max,int value)
{
  FSUSBElementInfoMap returnMap(0,1,LastInput,FSInputChanged);
  for(unique_ptr_of_managers & manager : managers)
  {
      returnMap =  manager->lookUpDeviceInputFromUSBID(vendorUSBID, productUSBID , controlID, min, max, value);
      if(returnMap.getDeviceInput() != LastInput)
      {

          break;
      }
  }
  return returnMap;
}

FSUSBElementInfoMap FSWindowsJoystickDeviceManager::infoMapForInputType(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor )
{
    FSUSBElementInfoMap returnMap(0,1,LastInput,FSInputChanged);
    for(unique_ptr_of_managers & manager : managers)
    {
        returnMap = manager->infoMapForInputType(vendorUSBID, productUSBID , inputToLookFor);
        if(returnMap.getDeviceInput() != LastInput)
        {
            break;
        }
    }
    return returnMap;
}
bool FSWindowsJoystickDeviceManager::doesDeviceHaveDeviceInput(unsigned int deviceID,FSDeviceInput inputToLookFor)
{
    Does_Have_Device_Input(doesDeviceHaveDeviceInput( deviceID, inputToLookFor))
}

bool FSWindowsJoystickDeviceManager::doesElementHaveDeviceInputForValue(unsigned int vendorUSBID, unsigned int productUSBID ,unsigned int elementID,FSDeviceInput inputToLookFor )
{
    Does_Have_Device_Input(doesElementHaveDeviceInputForValue(vendorUSBID,  productUSBID , elementID, inputToLookFor ))
}

bool FSWindowsJoystickDeviceManager::doesDeviceHaveDeviceInput(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor)
{
    Does_Have_Device_Input(doesDeviceHaveDeviceInput(vendorUSBID, productUSBID ,inputToLookFor))
}

bool FSWindowsJoystickDeviceManager::doesDeviceHaveDeviceInputForValue(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor,int value )
{
    Does_Have_Device_Input(doesDeviceHaveDeviceInputForValue( vendorUSBID, productUSBID , inputToLookFor, value))
}

bool FSWindowsJoystickDeviceManager::doesDeviceHaveDeviceInputForValue(unsigned int deviceID,FSDeviceInput inputToLookFor,  int value )
{
    Does_Have_Device_Input(doesDeviceHaveDeviceInputForValue( deviceID,inputToLookFor, value))
}



