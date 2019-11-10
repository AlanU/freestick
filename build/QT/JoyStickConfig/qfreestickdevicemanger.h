#ifndef QFREESTICKDEVICEMANGER_H
#define QFREESTICKDEVICEMANGER_H
#include <freestick.h>
#include <QObject>

class QFreestickDeviceManger: public QObject
{
    Q_OBJECT
public:
    virtual ~QFreestickDeviceManger();
    explicit QFreestickDeviceManger(FreeStickDeviceManager * deviceManager,QObject *parent = nullptr);
    QFreestickDeviceManger() = delete;
    QFreestickDeviceManger(QObject *parent = nullptr) = delete;
    Q_PROPERTY(FreeStickDeviceManager* freestickManager READ freestickManager NOTIFY freestickManagerChanged);
    FreeStickDeviceManager * freestickManager();
signals:
    void freestickManagerChanged();

private:
    FreeStickDeviceManager * m_manager = nullptr;// does not own mananger
};

#endif // QFREESTICKDEVICEMANGER_H
