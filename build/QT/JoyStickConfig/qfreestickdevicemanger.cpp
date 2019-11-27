#include "qfreestickdevicemanger.h"

QFreestickDeviceManger::~QFreestickDeviceManger()
{
    m_manager = nullptr;
}

QFreestickDeviceManger::QFreestickDeviceManger(std::shared_ptr<FreeStickDeviceManager>  deviceManager,QObject *parent):QObject(parent)
{
    m_manager = deviceManager;
    emit freestickManagerChanged();
}


std::weak_ptr<FreeStickDeviceManager> QFreestickDeviceManger::freestickManager()
{
    return m_manager;
}
