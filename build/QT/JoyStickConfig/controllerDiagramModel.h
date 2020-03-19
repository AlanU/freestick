#pragma once
#include "freestick.h"
#include <QAbstractListModel>
#include "qfreestickdevicemanger.h"
#include "baseDeviceModel.h"
using namespace freestick;

class ControllerDiagramModel :public BaseDeviceModel
{
    Q_OBJECT
public:
    ControllerDiagramModel();

    Q_PROPERTY(unsigned int joystickID READ joystickID WRITE setJoystickID NOTIFY joystickIDChanged)

    int joystickID();
    void setJoystickID(unsigned int newID);

    Q_PROPERTY(float aButton READ aButton WRITE setaButton NOTIFY aButtonChanged);
    float aButton() const;
    virtual void setaButton(float value);

    Q_PROPERTY(float bButton READ aButton WRITE setbButton NOTIFY bButtonChanged);
    float bButton() const;
    virtual void setbButton(float value);

    Q_PROPERTY(float xButton READ aButton WRITE setxButton NOTIFY xButtonChanged);
    float xButton() const;
    virtual void setxButton(float value);

    Q_PROPERTY(float yButton READ aButton WRITE setyButton NOTIFY yButtonChanged);
    float yButton() const;
    virtual void setyButton(float value);

    QHash<int,QByteArray> roleNames() const override {return QHash<int,QByteArray>();};
    int rowCount(const QModelIndex & /*parent = QModelIndex()*/) const override {return 0;};
    QVariant data(const QModelIndex &/*index*/, int /*role = Qt::DisplayRole*/) const override{return QVariant();};


    void onButtonDown(FSDeviceInputEvent event) override;
    void onButtonUp(FSDeviceInputEvent event) override;
    void onStickMove(FSDeviceInputEvent event) override;


signals:
    void joystickIDChanged(int newID);
    void aButtonChanged(float value);
    void bButtonChanged(float value);
    void xButtonChanged(float value);
    void yButtonChanged(float value);
protected:
    void updateControllerValues(FSDeviceInputEvent & event);
    void updateModel(unsigned int joystickiD);

private:
    unsigned int m_joystickId = -1;
    float m_aButton = 0.0f;
    float m_bButton = 0.0f;
    float m_xButton = 0.0f;
    float m_yButton = 0.0f;
};

