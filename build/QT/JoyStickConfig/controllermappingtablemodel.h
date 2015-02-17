#ifndef CONTROLLERMAPPINGTABLEMODEL_H
#define CONTROLLERMAPPINGTABLEMODEL_H

#include "freestick.h"
#include <QAbstractTableModel>

using namespace freestick;
class ControllerMappingTableModel : public QAbstractTableModel ,public  freestick::IFSJoystickListener
{
public:
    ControllerMappingTableModel(FreeStickDeviceManager & manager,unsigned int joystickiD);
    int rowCount(const QModelIndex & /*parent*/) const;
    int columnCount(const QModelIndex & /*parent*/) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual ~ControllerMappingTableModel();
    virtual void onButtonDown(FSDeviceInputEvent event);
    virtual void onButtonUp(FSDeviceInputEvent event);
    virtual void onStickMove(FSDeviceInputEvent event);
    virtual void onDisconnect(FSBaseEvent event) ;
    virtual void onConnect(FSBaseEvent event) ;
private:
    ControllerMappingTableModel();
    FreeStickDeviceManager * _manager;
    int _joystickId;
    JoyStickElementMap _JoyStickElementMap;
    std::vector<unsigned int> _elemntIDList;
    void modelChanged(int joystickiD);
    void elementChanged(unsigned int elementID);
    std::vector<bool> _elemnetMapped;

};

#endif // CONTROLLERMAPPINGTABLEMODEL_H
