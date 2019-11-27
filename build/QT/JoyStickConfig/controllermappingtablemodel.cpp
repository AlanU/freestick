#include "controllermappingtablemodel.h"
#include <string>
#include <array>
//This is not the full page map
const std::array<const std::string,16> usagePageList  {"Undefined",
                                                    "Generic Desktop",
                                                    "Simulation Controls",
                                                   "VR Controls",
                                                   "Sports Controls",
                                                   "Game Controls",
                                                   "Generic Device Controls",
                                                   "Keyboard/Keypad",
                                                   "LEDs",
                                                   "Button",
                                                   "Ordinal",
                                                   "Telephony",
                                                   "Consumer",
                                                   "Digitizer",
                                                   "PID Page",
                                                   "Unicode"};
/*const std::array<const std::map<uint16_t,const std::string>,16>  usageList { {
                                                                 {0x00,"Undefined"},
                                                                 {0x01,"Pointer"},
                                                                 {0x02,"Mouser"},
                                                                 {0x03,"Reserved"},
                                                                 {0x04,"Joystick"},
                                                                 {0x05,"Game Pad"},
                                                                 {0x06,"Keyboard"},
                                                                 {0x07,"KeyPad"},
                                                                 {0x08,"Multi-axis Controller"},
                                                                 {0x09,"Table PC System Controls"},
                                                                 {0x30,"X"},
                                                                 {0x31,"Y"},
                                                                 {0x32,"Z"},
                                                                 {0x33,"Rx"},
                                                                 {0x34,"Ry"},
                                                                 {0x35,"Rz"},
                                                                 {0x36,"Slider"},
                                                                 {0x37,"Dial"},
                                                                 {0x38,"Wheel"},
                                                                 {0x39,"Hat switch"},
                                                                 {0x3A,"Counted Buffer"}}};*/

ControllerMappingTableModel::ControllerMappingTableModel(std::weak_ptr<FreeStickDeviceManager> manager,unsigned int joystickID)
{
  //  _manager = &manager;
    setJoystickID(joystickID);
    setManager(manager);
    //modelChanged(joystickID);
    /*_manager->ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                 FS_JOYSTICK_DISCONNECT_EVENT |
                                                 FS_BUTTON_EVENT | FS_AXIS_EVENT
                                                 | FS_TRIGGER_EVENT,*this);*/

}

ControllerMappingTableModel::ControllerMappingTableModel()
{
}

unsigned int ControllerMappingTableModel::joystickID()
{
    return _joystickId;
}

void ControllerMappingTableModel::setJoystickID(unsigned int newID)
{
    modelChanged(newID);
    emit joystickIDChanged(newID);
}

QFreestickDeviceManger* ControllerMappingTableModel::manager()
{
    return _wrapperManger;
}

void ControllerMappingTableModel::setManager(QFreestickDeviceManger * manager)
{
    setManager(manager->freestickManager());

    _wrapperManger = manager;
    emit managerChanged(_wrapperManger);
}

void ControllerMappingTableModel::setManager(std::weak_ptr<FreeStickDeviceManager> manager)
{
    if(!_manager.expired())
    {
        _manager.lock()->UnListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                 FS_JOYSTICK_DISCONNECT_EVENT |
                                                 FS_BUTTON_EVENT | FS_AXIS_EVENT
                                                 | FS_TRIGGER_EVENT,*this);
    }

    _manager = manager;

    if(!_manager.expired())
    {
        _manager.lock()->ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                  FS_JOYSTICK_DISCONNECT_EVENT |
                                                  FS_BUTTON_EVENT | FS_AXIS_EVENT
                                                  | FS_TRIGGER_EVENT,*this);
    }

}

ControllerMappingTableModel::~ControllerMappingTableModel()
{
    if(!_manager.expired())
    {
         _manager.lock()->UnListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                 FS_JOYSTICK_DISCONNECT_EVENT |
                                                 FS_BUTTON_EVENT | FS_AXIS_EVENT
                                                 | FS_TRIGGER_EVENT,*this);
    }
    _wrapperManger = nullptr;
    _elemnetMapped.clear();
    _elementValuelist.clear();
    _elemntIDList.clear();

}

int ControllerMappingTableModel::rowCount(const QModelIndex & /*parent*/) const
 {

    return static_cast<int>(_elemntIDList.size());
 }

 int ControllerMappingTableModel::columnCount(const QModelIndex & /*parent*/) const
 {
     return 11;
 }

 QHash<int, QByteArray> ControllerMappingTableModel::roleNames() const {
     QHash<int, QByteArray> roles;
     roles[id] = "ID";
     roles[minValueRange] = "Min_Value_Range";
     roles[maxValueRange] = "Max_Value_Range";
     roles[rawValue] =  "Raw_Value";
     roles[value] = "Value";
     roles[deadMin] = "Dead_Min";
     roles[deadMax] =  "Dead_Max";
     roles[mapped] = "Mapped";
     roles[elementCookie] = "Element_Cookie";
     roles[usagePage] =  "Usage_Page";
     roles[usage] =  "Usage";
     roles[Qt::DisplayRole] = "display";
     return roles;
 }



 QVariant ControllerMappingTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
     if(role == Qt::DisplayRole && orientation ==  Qt::Horizontal)
     {
            QString role = "";
            switch(section)
             {
                  case id:
                     role = tr("ID");
                  break;
                  case minValueRange:
                     role = tr( "Min Value Range");
                  break;
                  case maxValueRange:
                    role = tr("Max Value Range");
                  break;
                  case rawValue:
                    role = tr("Raw Value");
                  break;
                  case value:
                    role = tr("Value");
                  break;
                  case deadMin:
                    role = tr("Dead Min");
                   break;
                  case deadMax:
                    role = tr("Dead Max");
                   break;
                  case mapped:
                    role = tr("Mapped");
                  break;
                  case elementCookie:
                    role = tr("Element Cookie");
                  break;
                  case usagePage:
                    role = tr("Usage Page");
                  break;
                  case usage:
                    role = tr("Usage");
                  break;
                  default:
                    break;
             }
            return role;

     }
     return QVariant();

 }

 QVariant ControllerMappingTableModel::dataFromCol(const unsigned int col,const unsigned int row) const
 {
     QVariant data;
     unsigned int elementID =_elemntIDList[row];
     FSUSBJoyStickInputElement element = _JoyStickElementMap.at(elementID);
     switch(col)
     {
     case 0:
         data = static_cast<quint32>(_elemntIDList[row]);
     break;
     case 1:
         data =  static_cast<qlonglong>(element.getMinValue());
     break;
     case 2:
         data =  static_cast<qlonglong>(element.getMaxValue());
     break;
     case 3:
         data =  static_cast<qlonglong>(element.getValue());
     break;
     case 4:
         data =  static_cast<QVariant>(_elementValuelist[row]);
      break;
     case 5:
         data =  static_cast<qlonglong>(element.getDeadZoneMin());
     break;
     case 6:
         data =  static_cast<qlonglong>(element.getDeadZoneMax());
      break;
     case 7:
         data =  static_cast<QVariant>(_elemnetMapped[row]);
      break;
     case 8:
         data = static_cast<qlonglong>(element.getButtonNumber());
      break;
     case 9:
     {
         quint16 usagePage = static_cast<quint16>(FSUSBJoystickDeviceManager::getUsagePageForElement(_elemntIDList[row]));
         if(usagePage < usagePageList.size())
         {
             data =  tr(usagePageList[usagePage].c_str());
         }
         data =  usagePage;
     }
     break;
     case 10:
         data =  static_cast<quint16>(FSUSBJoystickDeviceManager::getUsageForElement(_elemntIDList[row]));
     break;
     default:
         break;
     }
     return data;
 }

 QVariant ControllerMappingTableModel::data(const QModelIndex &index, int role) const
 {
     if (role == Qt::ToolTipRole)
     {
         switch (index.column()) {
         case 9:
         {
             quint16 usagePage = static_cast<quint16>(FSUSBJoystickDeviceManager::getUsagePageForElement(_elemntIDList[index.row()]));
             if(usagePage < usagePageList.size())
             {
                 return usagePage;
             }
         }
             break;
         default:
             break;
         }
     }
     if (role == Qt::DisplayRole)
     {
        //QString("%1, %2").arg(index.column()).arg(index.row());
        return QString(dataFromCol(index.column(),index.row()).toString());
      }
     else if(role > firstSectionType &&  role < lastSectionType)
     {
         // int firstNum = firstSectionType;
        // int lastNum = lastSectionType;
       //  int idNum = id;
        // int col = index.column();
       // int row = index.row();
        return dataFromCol((role-firstSectionType)-1,index.row());
     }
     return QVariant();
 }


void ControllerMappingTableModel::modelChanged(unsigned int joystickID)
{
    if(!_manager.expired() && _manager.lock()->getDevice(joystickID))
    {
        beginResetModel();
        _joystickId = joystickID;

        const FSUSBJoystick *  joystick = static_cast<const FSUSBJoystick *>(_manager.lock()->getDevice(joystickID));

        _JoyStickElementMap = joystick->getElements();
        _elemntIDList = joystick->getElementIds();
        for(unsigned int index = 0; index < _elemntIDList.size(); index++)
        {
            _elemnetMapped.push_back(false);
            _elementValuelist.push_back(0);
        }
        endResetModel();
    }
}

void ControllerMappingTableModel::elementChanged(unsigned int elementID,float newValue)
{
    if(!_manager.expired())
    {
        const FSUSBJoystick *  joystick = static_cast<const FSUSBJoystick *>(_manager.lock()->getDevice(_joystickId));

        const FSUSBJoyStickInputElement * element = joystick->findInputElement(elementID) ;

        if(element != nullptr)
        {
            FSUSBJoyStickInputElement *  elementCopy = &_JoyStickElementMap[elementID];
            elementCopy->setValue(element->getValue());
        }

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
void ControllerMappingTableModel::onDisconnect(FSBaseEvent /*event*/)
{

}

 void ControllerMappingTableModel::onConnect(FSBaseEvent /*event*/)
{
     //setJoystickID(event.getDeviceID());
    //event;//To remove warning
}
