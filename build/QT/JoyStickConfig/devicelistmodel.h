#pragma once
#include "freestick.h"
#include <QAbstractListModel>
#include "qfreestickdevicemanger.h"
#include "baseDeviceModel.h"
using namespace freestick;

class DeviceListModel : public BaseDeviceModel
{
    Q_OBJECT
public:
    DeviceListModel();
    virtual ~DeviceListModel();
    enum DeviceRoles{
        modelDataRole = Qt::UserRole + 1,
    };

    QHash<int,QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void onButtonDown(FSDeviceInputEvent event) override;
    void onButtonUp(FSDeviceInputEvent event) override;
    void onStickMove(FSDeviceInputEvent event) override;
    void onDisconnect(FSBaseEvent event) override;
    void onConnect(FSBaseEvent event) override;

    Q_INVOKABLE QVariant getIdFromIndex(QVariant index) override;

private:
    QVector<QPair<QString,unsigned int>> m_data;

};

