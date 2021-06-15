#include "baseDeviceModel.h"

BaseDeviceModel::BaseDeviceModel():QAbstractListModel()
{

}

BaseDeviceModel::~BaseDeviceModel()
{

}

QFreestickDeviceManger* BaseDeviceModel::manager()
{
    return m_wrapperManger;
}

void BaseDeviceModel::setManager(QFreestickDeviceManger* manager)
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
                                                                  FS_JOYSTICK_DISCONNECT_EVENT |
                                                                  FS_BUTTON_EVENT |
                                                                  FS_AXIS_EVENT,
                                                                   *this);
        }
    }

    emit managerChanged(manager);
}


void BaseDeviceModel::onButtonDown(FSDeviceInputEvent /*event*/)
{

}
void BaseDeviceModel::onButtonUp(FSDeviceInputEvent /*event*/)
{

}
void BaseDeviceModel::onStickMove(FSDeviceInputEvent event)
{

}

void BaseDeviceModel::onDisconnect(FSBaseEvent /*event*/)
{

}

void BaseDeviceModel::onConnect(FSBaseEvent /*event*/)
{

}
//TODO figure out how to remove
QVariant BaseDeviceModel::getIdFromIndex(QVariant /*index*/)
{
    return QVariant();
}
