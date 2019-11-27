#ifndef CONTROLLERMAPPINGTABLEMODEL_H
#define CONTROLLERMAPPINGTABLEMODEL_H

#include "freestick.h"
#include <QAbstractTableModel>
#include "qfreestickdevicemanger.h"
using namespace freestick;
typedef enum
{
    firstSectionType = Qt::UserRole + 1,
    id ,
    minValueRange ,
    maxValueRange ,
    rawValue ,
    value ,
    deadMin ,
    deadMax ,
    mapped ,
    elementCookie ,
    usagePage,
    usage,
    lastSectionType
} sectionType;
/*typedef enum
{
    id = 0,
    minValueRange = 1,
    maxValueRange = 2,
    rawValue = 3,
    value = 4,
    deadMin = 5,
    deadMax = 6,
    mapped = 7,
    elementCookie = 8,
    usagePage = 9,
    usage = 10
} sectionType;*/

class ControllerMappingTableModel : public QAbstractTableModel ,public  freestick::IFSJoystickListener
{
    Q_OBJECT
public:
    ControllerMappingTableModel();
    ControllerMappingTableModel(std::weak_ptr<FreeStickDeviceManager> manager,unsigned int joystickiD);
    int rowCount(const QModelIndex & /*parent*/) const override;
    int columnCount(const QModelIndex & /*parent*/) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    Q_PROPERTY(QFreestickDeviceManger* manager READ manager WRITE setManager NOTIFY managerChanged)
    Q_PROPERTY(unsigned int joystickID READ joystickID WRITE setJoystickID NOTIFY joystickIDChanged)

    unsigned int joystickID();
    void setJoystickID(unsigned int newID);

    QFreestickDeviceManger* manager();
    void setManager(QFreestickDeviceManger* manager);
    void setManager(std::weak_ptr<FreeStickDeviceManager> manager);

    virtual QHash<int, QByteArray> roleNames() const override;

    virtual  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual ~ControllerMappingTableModel() override;
    virtual void onButtonDown(FSDeviceInputEvent event) override;
    virtual void onButtonUp(FSDeviceInputEvent event) override;
    virtual void onStickMove(FSDeviceInputEvent event) override;
    virtual void onDisconnect(FSBaseEvent event) override;
    virtual void onConnect(FSBaseEvent event) override ;
signals:
    void joystickIDChanged(unsigned int newID);
    void managerChanged(QFreestickDeviceManger* manager);
private:
    QVariant dataFromCol(const unsigned int col,const unsigned int row) const;
    QFreestickDeviceManger * _wrapperManger = nullptr;
    std::weak_ptr<FreeStickDeviceManager> _manager;
    unsigned int _joystickId = 0;
    JoyStickElementMap _JoyStickElementMap;
    std::vector<idNumber> _elemntIDList;
    void modelChanged(unsigned int joystickiD);
    void elementChanged(unsigned int elementID,float newValue);
    std::vector<bool> _elemnetMapped;
    std::vector<float> _elementValuelist;

};

#endif // CONTROLLERMAPPINGTABLEMODEL_H
