#pragma once
#include "freestick.h"
#include <QAbstractListModel>
#include "qfreestickdevicemanger.h"
using namespace freestick;

class DeviceListModel : public QAbstractListModel ,public  freestick::IFSJoystickListener
{
    Q_OBJECT
public:
    DeviceListModel();
    ~DeviceListModel() override;
    enum DeviceRoles{
        modelDataRole = Qt::UserRole + 1,
    };

    Q_PROPERTY(QFreestickDeviceManger* manager READ manager WRITE setManager NOTIFY managerChanged)

    QFreestickDeviceManger* manager();
    void setManager(QFreestickDeviceManger* manager);
    QHash<int,QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void onButtonDown(FSDeviceInputEvent event) override;
    void onButtonUp(FSDeviceInputEvent event) override;
    void onStickMove(FSDeviceInputEvent event) override;
    void onDisconnect(FSBaseEvent event) override;
    void onConnect(FSBaseEvent event) override;

    Q_INVOKABLE QVariant getIdFromIndex(QVariant index);
signals:
    void managerChanged(QFreestickDeviceManger* manager);
private:
    std::weak_ptr<FreeStickDeviceManager> m_manager;
    QFreestickDeviceManger * m_wrapperManger = nullptr;//Does not own memory
    QVector<QPair<QString,unsigned int>> m_data;

};

