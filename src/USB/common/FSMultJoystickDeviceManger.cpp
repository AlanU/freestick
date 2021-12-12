#include "USB/common/FSMultJoystickDeviceManger.h"
#include <algorithm>
using namespace freestick;

bool FSMultJoystickDeviceManger::DoesDeviceHaveInput(std::function<bool(unique_ptr_of_managers&)>const &func)
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


FSMultJoystickDeviceManger::FSMultJoystickDeviceManger()
{

}

FSMultJoystickDeviceManger::~FSMultJoystickDeviceManger()
{
    managers.clear();
}

void FSMultJoystickDeviceManger::ListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener)
{
    std::for_each(managers.begin(),managers.end(),
                  [eventFlags,&listener](unique_ptr_of_managers &manager){manager->ListenForAllJoysticksForEventTypes(eventFlags, listener);});
}

void FSMultJoystickDeviceManger::UnListenForAllJoysticksForEventTypes(unsigned int eventFlags,IFSJoystickListener & listener)
{

    std::for_each(managers.begin(),managers.end(),[eventFlags,&listener](unique_ptr_of_managers &manager){manager->UnListenForAllJoysticksForEventTypes(eventFlags, listener);});
}


void FSMultJoystickDeviceManger::init( )
{

   for_each(managers.begin(),managers.end(),[this](unique_ptr_of_managers &manager){
        static_cast<FSBaseManager*>(manager.get())->init(this);});
}

void FSMultJoystickDeviceManger::update()
{
   for_each(managers.begin(),managers.end(),[](unique_ptr_of_managers &manager){
       manager->update();});
}

const FSBaseDevice * FSMultJoystickDeviceManger::getDevice(elementID deviceID)
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

void FSMultJoystickDeviceManger::vibrateController(idNumber deviceID)
{
   managerType * manager = findManagerForDevice(deviceID);
   if(manager != nullptr)
   {
       manager->vibrateController(deviceID);
   }
}

managerType * FSMultJoystickDeviceManger::findManagerForDevice(elementID deviceID)
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

elementID FSMultJoystickDeviceManger::getNextID()
{
    static unsigned int ID = 1;//0 is reserved for errors
    return (ID++);
}

void FSMultJoystickDeviceManger::addMapping(vendorIDType vendorUSBID, productIDType productUSBID, idNumber controlUSBID,FSDeviceInput deviceInput)
{

    std::for_each(managers.begin(),managers.end(),
                  [vendorUSBID,productUSBID,controlUSBID,&deviceInput](unique_ptr_of_managers &manager)
    {manager->addMapping(vendorUSBID, productUSBID, controlUSBID, deviceInput);});
}

void FSMultJoystickDeviceManger::addMapping(idNumber deviceID,idNumber controlID,FSDeviceInput deviceInput)
{
     std::for_each(managers.begin(),managers.end(),
                   [deviceID,controlID,&deviceInput](unique_ptr_of_managers &manager)
     {manager->addMapping(deviceID,controlID, deviceInput);});
}

FSUSBElementInfoMap FSMultJoystickDeviceManger::lookUpDeviceInputFromID(idNumber deviceID, idNumber controlID, minMaxNumber min, minMaxNumber max,physicalValueNumber value)
{
    managerType * managerForDevice = findManagerForDevice(deviceID);
    if(managerForDevice != nullptr)
    {
        return managerForDevice->lookUpDeviceInputFromID(deviceID, controlID, min, max, value);
    }
    return FSUSBElementInfoMap(0,1,LastInput,FSInputChanged);
}

FSUSBElementInfoMap FSMultJoystickDeviceManger::lookUpDeviceInputFromUSBID(vendorIDType vendorUSBID, productIDType productUSBID , idNumber controlID, minMaxNumber min,minMaxNumber max,physicalValueNumber value)
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

FSUSBElementInfoMap FSMultJoystickDeviceManger::infoMapForInputType(vendorIDType vendorUSBID, productIDType productUSBID ,FSDeviceInput inputToLookFor )
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

bool FSMultJoystickDeviceManger::doesDeviceHaveDeviceInput(idNumber deviceID,FSDeviceInput inputToLookFor)
{
   return DoesDeviceHaveInput([deviceID,&inputToLookFor](unique_ptr_of_managers &manager) {
        return manager->doesDeviceHaveDeviceInput( deviceID, inputToLookFor);});
}

bool FSMultJoystickDeviceManger::doesElementHaveDeviceInputForValue(vendorIDType vendorUSBID, productIDType productUSBID ,idNumber elementID,FSDeviceInput inputToLookFor )
{
    return DoesDeviceHaveInput([vendorUSBID, productUSBID, elementID,&inputToLookFor](unique_ptr_of_managers &manager) {
         return manager->doesElementHaveDeviceInputForValue( vendorUSBID,  productUSBID , elementID, inputToLookFor );});
}





