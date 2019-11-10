#include "qfreestickdevicemanger.h"

QFreestickDeviceManger::~QFreestickDeviceManger()
{

}

QFreestickDeviceManger::QFreestickDeviceManger(FreeStickDeviceManager * deviceManager,QObject *parent):QObject(parent)
{
    m_manager = deviceManager;
    emit freestickManagerChanged();
}


FreeStickDeviceManager * QFreestickDeviceManger::freestickManager()
{
    return m_manager;
}
