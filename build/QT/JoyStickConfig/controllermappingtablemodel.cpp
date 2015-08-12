#include "controllermappingtablemodel.h"

ControllerMappingTableModel::ControllerMappingTableModel(FreeStickDeviceManager & manager,unsigned int joystickID)
{
    _manager = &manager;
    modelChanged(joystickID);
    _manager->ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                 FS_JOYSTICK_DISCONNECT_EVENT |
                                                 FS_BUTTON_EVENT | FS_AXIS_EVENT
                                                 | FS_TRIGGER_EVENT,*this);

}

ControllerMappingTableModel::ControllerMappingTableModel()
{

}

ControllerMappingTableModel::~ControllerMappingTableModel()
{
    _manager->UnListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                 FS_JOYSTICK_DISCONNECT_EVENT |
                                                 FS_BUTTON_EVENT | FS_AXIS_EVENT
                                                 | FS_TRIGGER_EVENT,*this);

}

int ControllerMappingTableModel::rowCount(const QModelIndex & /*parent*/) const
 {

    return _elemntIDList.size() ;
 }

 int ControllerMappingTableModel::columnCount(const QModelIndex & /*parent*/) const
 {
     return 9;
 }


 QVariant ControllerMappingTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
     if(role == Qt::DisplayRole && orientation ==  Qt::Horizontal)
     {
            switch(section)
             {
                  case 0:
                     return tr("ID");
                  break;
                  case 1:
                     return tr( "Min Value Range");
                  break;
                  case 2:
                    return tr("Max Value Range");
                  break;
                  case 3:
                    return tr("Raw Value");
                  break;
                  case 4:
                    return tr("Value");
                  break;
                  case 5:
                    return tr("Dead Min");
                   break;
                  case 6:
                    return tr("Dead Max");
                   break;
                  case 7:
                    return tr("Mapped");
                  break;
                  case 8:
                    return tr("Element Cookie");
                  break;
                  default:
                    break;
             }

     }
     return QVariant();

 }
 QVariant ControllerMappingTableModel::data(const QModelIndex &index, int role) const
 {
     if (role == Qt::DisplayRole)
     {
         unsigned int id =_elemntIDList[index.row()];
        FSUSBJoyStickInputElement element = _JoyStickElementMap.at(id);

        switch(index.column())
        {
        case 0:
            return static_cast<quint32>(_elemntIDList[index.row()]);
        break;
        case 1:
            return static_cast<qlonglong>(element.getMinValue());
        break;
        case 2:
            return static_cast<qlonglong>(element.getMaxValue());
        break;
        case 3:
            return static_cast<qlonglong>(element.getValue());
        break;
        case 4:
            return static_cast<QVariant>(_elementValuelist[index.row()]);
         break;
        case 5:
            return static_cast<qlonglong>(element.getDeadZoneMin());
        break;
        case 6:
            return static_cast<qlonglong>(element.getDeadZoneMax());
         break;
        case 7:
            return static_cast<QVariant>(_elemnetMapped[index.row()]);
         break;
        case 8:
            return static_cast<qlonglong>(element.getButtonNumber());
        default:
            break;
        }
     }
     return QVariant();
 }


void ControllerMappingTableModel::modelChanged(int joystickID)
{
    beginResetModel();
    _joystickId = joystickID;

    const FSUSBJoystick *  joystick = static_cast<const FSUSBJoystick *>(_manager->getDevice(joystickID));

    _JoyStickElementMap = joystick->getElements();
    _elemntIDList = joystick->getElementIds();
    for(int index = 0; index < _elemntIDList.size(); index++)
    {
        _elemnetMapped.push_back(false);
        _elementValuelist.push_back(0);
    }
    endResetModel();


}

void ControllerMappingTableModel::elementChanged(unsigned int elementID,float newValue)
{
    const FSUSBJoystick *  joystick = static_cast<const FSUSBJoystick *>(_manager->getDevice(_joystickId));

    const FSUSBJoyStickInputElement * element = joystick->findInputElement(elementID) ;


    FSUSBJoyStickInputElement *  elementCopy = &_JoyStickElementMap[elementID];
elementCopy->setValue(element->getValue());

    for(unsigned int index = 0 ; index < _elemntIDList.size(); index++)
    {
        if(_elemntIDList[index] == elementID)
        {

              _elemnetMapped[index] = true;
              _elementValuelist[index]=newValue;
              QModelIndex topLeft = createIndex(index,0);
                QModelIndex bottom = createIndex(index,4);
               dataChanged(topLeft,bottom);
               return ;
        }

    }

}

void ControllerMappingTableModel::onButtonDown(FSDeviceInputEvent event)
{
    if(event.getDeviceID() != _joystickId)
         return ;

    elementChanged(event.getControlID(),event.getNewInputValue());

}

void ControllerMappingTableModel::onButtonUp(FSDeviceInputEvent event)
{
    if(event.getDeviceID() != _joystickId)
         return ;

    elementChanged(event.getControlID(),event.getNewInputValue());

}

void ControllerMappingTableModel::onStickMove(FSDeviceInputEvent event)
{
    if(event.getDeviceID() != _joystickId)
         return ;

    elementChanged(event.getControlID(),event.getNewInputValue());


}
void ControllerMappingTableModel::onDisconnect(FSBaseEvent event)
{

}

 void ControllerMappingTableModel::onConnect(FSBaseEvent event)
{

}
