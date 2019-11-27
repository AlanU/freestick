#include "devicelistmodel.h"
#include <QHash>
using namespace freestick;
DeviceListModel::DeviceListModel():QAbstractListModel()
{

}

QFreestickDeviceManger* DeviceListModel::manager()
{
    return m_wrapperManger;
}
void DeviceListModel::setManager(QFreestickDeviceManger* manager)
{
    if(!m_manager.expired())
    {
        m_manager.lock()->UnListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                        FS_JOYSTICK_DISCONNECT_EVENT,
                                                         *this);
    }

    if(manager)
    {
        m_wrapperManger = manager;
        m_manager = m_wrapperManger->freestickManager();
        if(!m_manager.expired())
        {
             m_manager.lock()->ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                      FS_JOYSTICK_DISCONNECT_EVENT ,
                                                      *this);
        }
    }

    emit managerChanged(manager);
}

DeviceListModel::~DeviceListModel()
{
    if(!m_manager.expired())
    {
        m_manager.lock()->UnListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                        FS_JOYSTICK_DISCONNECT_EVENT,
                                                         *this);
    }
    m_wrapperManger = nullptr;
    m_data.clear();
}


QHash<int,QByteArray> DeviceListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "dislpay";
    return roles;
}

int DeviceListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_data.size();
}

QVariant DeviceListModel::data(const QModelIndex &index, int role) const
{
   if(role == Qt::DisplayRole && m_data.size() > index.row()){
       return m_data[index.row()].first;
   }
   return QVariant();
}

QVariant DeviceListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void DeviceListModel::onButtonDown(FSDeviceInputEvent event)
{

}
void DeviceListModel::onButtonUp(FSDeviceInputEvent event)
{

}
void DeviceListModel::onStickMove(FSDeviceInputEvent event)
{

}

void DeviceListModel::onDisconnect(FSBaseEvent event)
{
    auto id = event.getDeviceID();
    for(int index = m_data.size()-1; index >= 0;++index)
    {
        if(id == m_data[index].second)
        {
            beginResetModel();
            m_data.remove(index);
            endResetModel();
            return;
        }
    }
}

void DeviceListModel::onConnect(FSBaseEvent event)
{
    if(!m_manager.expired())
    {
        beginResetModel();
        auto contoller =  m_manager.lock()->getDevice(event.getDeviceID());
        QString name (contoller->GetFrendlyName().c_str());
        m_data.push_back(QPair<QString,unsigned int>(name,event.getDeviceID()));
        endResetModel();
    }
}

QVariant DeviceListModel::getIdFromIndex(QVariant index)
{
   if(index.toInt() >= 0 && m_data.size() > index.toInt())
   {
       return  m_data[index.toInt()].second;
   }
   return QVariant();
}

