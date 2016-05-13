#include "USB/platform/Windows/FSWindowsJoystickDeviceManager.h"

using namespace freestick;

bool FSWindowsJoystickDeviceManager::DoesDeviceHaveInput(std::function<bool(unique_ptr_of_managers&)>const &func)
{
    bool result = false;
    for(unique_ptr_of_managers & manager : managers)
    {
        if(func(manager))
        {
            result = true;
            break;
        }
    }
    return result;
}


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
    std::for_each(managers.begin(),managers.end(),
                  [eventFlags,&listener](unique_ptr_of_managers &manager){manager->ListenForAllJoysticksForEventTypes(eventFlags, listener);});
}

void FSWindowsJoystickDeviceManager::UnListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener)
{

    std::for_each(managers.begin(),managers.end(),[eventFlags,&listener](unique_ptr_of_managers &manager){manager->UnListenForAllJoysticksForEventTypes(eventFlags, listener);});
}


void FSWindowsJoystickDeviceManager::init( )
{

   for_each(managers.begin(),managers.end(),[this](unique_ptr_of_managers &manager){
        static_cast<FSBaseManager*>(manager.get())->init(this);});
}

void FSWindowsJoystickDeviceManager::update()
{
   for_each(managers.begin(),managers.end(),[](unique_ptr_of_managers &manager){
       manager->update();});
}

const FSBaseDevice * FSWindowsJoystickDeviceManager::getDevice(ElementID deviceID)
{
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

void FSWindowsJoystickDeviceManager::addMapping(unsigned int vendorUSBID,unsigned int productUSBID,unsigned int controlUSBID,FSDeviceInput deviceInput)
{

    std::for_each(managers.begin(),managers.end(),
                  [vendorUSBID,productUSBID,controlUSBID,&deviceInput](unique_ptr_of_managers &manager)
    {manager->addMapping(vendorUSBID, productUSBID, controlUSBID, deviceInput);});
}

void FSWindowsJoystickDeviceManager::addMapping(unsigned int deviceID,unsigned int controlID,FSDeviceInput deviceInput)
{
     std::for_each(managers.begin(),managers.end(),
                   [deviceID,controlID,&deviceInput](unique_ptr_of_managers &manager)
     {manager->addMapping(deviceID,controlID, deviceInput);});
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
   return DoesDeviceHaveInput([deviceID,&inputToLookFor](unique_ptr_of_managers &manager) {
        return manager->doesDeviceHaveDeviceInput( deviceID, inputToLookFor);});
}

bool FSWindowsJoystickDeviceManager::doesElementHaveDeviceInputForValue(unsigned int vendorUSBID, unsigned int productUSBID ,unsigned int elementID,FSDeviceInput inputToLookFor )
{
    return DoesDeviceHaveInput([vendorUSBID, productUSBID, elementID,&inputToLookFor](unique_ptr_of_managers &manager) {
         return manager->doesElementHaveDeviceInputForValue( vendorUSBID,  productUSBID , elementID, inputToLookFor );});
}

bool FSWindowsJoystickDeviceManager::doesDeviceHaveDeviceInput(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor)
{
    return DoesDeviceHaveInput([vendorUSBID, productUSBID,&inputToLookFor](unique_ptr_of_managers &manager) {
         return manager->doesDeviceHaveDeviceInput( vendorUSBID,  productUSBID , inputToLookFor );});
}

bool FSWindowsJoystickDeviceManager::doesDeviceHaveDeviceInputForValue(unsigned int vendorUSBID, unsigned int productUSBID ,FSDeviceInput inputToLookFor,int value )
{

    return DoesDeviceHaveInput([vendorUSBID, productUSBID,&inputToLookFor,value](unique_ptr_of_managers &manager) {
         return manager->doesDeviceHaveDeviceInputForValue( vendorUSBID,  productUSBID , inputToLookFor ,value);});
}

bool FSWindowsJoystickDeviceManager::doesDeviceHaveDeviceInputForValue(unsigned int deviceID,FSDeviceInput inputToLookFor,  int value )
{
    return DoesDeviceHaveInput([deviceID,&inputToLookFor, value](unique_ptr_of_managers &manager) {
         return manager->doesDeviceHaveDeviceInputForValue( inputToLookFor,inputToLookFor ,value);});
}



