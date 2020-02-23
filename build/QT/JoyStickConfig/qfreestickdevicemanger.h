#ifndef QFREESTICKDEVICEMANGER_H
#define QFREESTICKDEVICEMANGER_H
#include <freestick.h>
#include <QObject>
#include <memory>
class QFreestickDeviceManger: public QObject
{
    Q_OBJECT
public:
    virtual ~QFreestickDeviceManger();
    explicit QFreestickDeviceManger(std::shared_ptr<FreeStickDeviceManager> deviceManager,QObject *parent = nullptr);
    QFreestickDeviceManger() = delete;
    QFreestickDeviceManger(QObject *parent = nullptr) = delete;
    Q_PROPERTY(std::weak_ptr<FreeStickDeviceManager> freestickManager READ freestickManager NOTIFY freestickManagerChanged)
    std::weak_ptr<FreeStickDeviceManager> freestickManager();
    Q_INVOKABLE qint32 getVendorID(qint32 controllerId);
    Q_INVOKABLE QString getVendorName(qint32 controllerId);
    Q_INVOKABLE qint32 getProductID(qint32 controllerId);
    Q_INVOKABLE QString getProductName(qint32 controllerId);
    Q_INVOKABLE QString getFriendlyName(qint32 controllerId);
signals:
    void freestickManagerChanged();

private:
    std::shared_ptr<FreeStickDeviceManager>m_manager;
};

#endif // QFREESTICKDEVICEMANGER_H
