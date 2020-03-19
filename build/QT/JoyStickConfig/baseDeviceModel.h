#pragma once
#include "freestick.h"
#include "qfreestickdevicemanger.h"
#include <QAbstractListModel>
#include <memory>
using namespace freestick;
class BaseDeviceModel : public QAbstractListModel, public  freestick::IFSJoystickListener
{
    Q_OBJECT
public:
    BaseDeviceModel();
    virtual ~BaseDeviceModel();
    Q_PROPERTY(QFreestickDeviceManger* manager READ manager WRITE setManager NOTIFY managerChanged)

    QFreestickDeviceManger* manager();
    virtual void setManager(QFreestickDeviceManger* manager);

    void onButtonDown(FSDeviceInputEvent event) override;
    void onButtonUp(FSDeviceInputEvent event) override;
    void onStickMove(FSDeviceInputEvent event) override;
    void onDisconnect(FSBaseEvent event) override;
    void onConnect(FSBaseEvent event) override;

    Q_INVOKABLE virtual QVariant getIdFromIndex(QVariant index);

signals:
    void managerChanged(QFreestickDeviceManger* manager);
protected:
    std::weak_ptr<FreeStickDeviceManager> m_manager;
    QFreestickDeviceManger * m_wrapperManger = nullptr;//Does not own memory
};

