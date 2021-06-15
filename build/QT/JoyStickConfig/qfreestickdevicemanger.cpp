#include "qfreestickdevicemanger.h"
#include <QVariant>
#include "freestick.h"
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
#define GET_DEVICE_PROPERTY(NAME,DEFAULT)  \
    const freestick::FSUSBJoystick * device = dynamic_cast<const freestick::FSUSBJoystick *>(m_manager->getDevice(controllerId)); \
    if(device) \
    { \
        return NAME; \
    } \
    return DEFAULT; \


qint32 QFreestickDeviceManger::getVendorID(qint32 controllerId)
{
    GET_DEVICE_PROPERTY(device->getVendorID(),-1)
}

QString QFreestickDeviceManger::getVendorName(qint32 controllerId)
{
    GET_DEVICE_PROPERTY(QString(device->getVendorFriendlyName().c_str()),QString())
}

qint32 QFreestickDeviceManger::getProductID(qint32 controllerId)
{
    GET_DEVICE_PROPERTY(device->getProductID(),-1)
}

QString QFreestickDeviceManger::getProductName(qint32 controllerId)
{
    GET_DEVICE_PROPERTY(QString(device->getProductFrendlyName().c_str()),"")

}

QString QFreestickDeviceManger::getFriendlyName(qint32 controllerId)
{
     GET_DEVICE_PROPERTY(QString(device->GetFrendlyName().c_str()),"")
}

QString QFreestickDeviceManger::gerFriendlyAPIName(qint32 controllerId){

    const freestick::FSUSBJoystick * device = dynamic_cast<const freestick::FSUSBJoystick *>(m_manager->getDevice(controllerId));
    QString apiString = "Unknown";
    if(device)
    {
        switch (device->getClassType()) {
         case freestick::FSBaseDeviceType:
            apiString = "Unknown Basic";
            break;
        case freestick::FSUSBDeviceType:
           apiString = "Unknown USB";
           break;
        case freestick::FSUSBJoystickType:
           apiString = "Unknown USB Joystick";
           break;
        case freestick::FSUSBMACOSXJoystickType:
           apiString = "macOS X Legacy ";
           break;
        case freestick::FSMFIJoystickType:
           apiString = "Apple MFI ";
           break;
        case freestick::FSAndroidJoystickType:
           apiString = "Android";
           break;
        case freestick::FSDirectInputJoystickType:
           apiString = "Windows DirectInput";
           break;
        case freestick::FSXInputJoystickType:
           apiString = "Windows XInput";
           break;
        case freestick::FSUSBNULLDeviceType:
           apiString = "FreeStrick Null Device";
           break;
        default:
            break;
        }
    }

    return apiString;
}

