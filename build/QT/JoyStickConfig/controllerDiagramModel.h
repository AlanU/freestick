#pragma once
#include "freestick.h"
#include <QAbstractListModel>
#include "qfreestickdevicemanger.h"
#include "baseDeviceModel.h"
using namespace freestick;                                                                   \
//TODO Convert all Q_PROPERTY to a maco
class ControllerDiagramModel :public BaseDeviceModel
{
    Q_OBJECT
public:
    ControllerDiagramModel();

    Q_PROPERTY(unsigned int joystickID READ joystickID WRITE setJoystickID NOTIFY joystickIDChanged)

    int joystickID();
    void setJoystickID(unsigned int newID);

    Q_PROPERTY(float upDpad READ upDpad WRITE setupDpad NOTIFY upDpadChanged);
    float upDpad() const;
    virtual void setupDpad(float value);

    Q_PROPERTY(float downDpad READ downDpad WRITE setdownDpad NOTIFY downDpadChanged);
    float downDpad() const;
    virtual void setdownDpad(float value);

    Q_PROPERTY(float leftDpad READ leftDpad WRITE setleftDpad NOTIFY leftDpadChanged);
    float leftDpad() const;
    virtual void setleftDpad(float value);

    Q_PROPERTY(float rightDpad READ rightDpad WRITE setrightDpad NOTIFY rightDpadChanged);
    float rightDpad() const;
    virtual void setrightDpad(float value);

    Q_PROPERTY(float aButton READ aButton WRITE setaButton NOTIFY aButtonChanged);
    float aButton() const;
    virtual void setaButton(float value);

    Q_PROPERTY(float bButton READ bButton WRITE setbButton NOTIFY bButtonChanged);
    float bButton() const;
    virtual void setbButton(float value);

    Q_PROPERTY(float xButton READ xButton WRITE setxButton NOTIFY xButtonChanged);
    float xButton() const;
    virtual void setxButton(float value);

    Q_PROPERTY(float yButton READ yButton WRITE setyButton NOTIFY yButtonChanged);
    float yButton() const;
    virtual void setyButton(float value);

    Q_PROPERTY(float centerButton READ centerButton WRITE setcenterButton NOTIFY centerButtonChanged);
    float centerButton() const;
    virtual void setcenterButton(float value);

    Q_PROPERTY(float startButton READ startButton WRITE setstartButton NOTIFY startButtonChanged);
    float startButton() const;
    virtual void setstartButton(float value);

    Q_PROPERTY(float selectButton READ selectButton WRITE setselectButton NOTIFY selectButtonChanged);
    float selectButton() const;
    virtual void setselectButton(float value);

    Q_PROPERTY(float l1Button READ l1Button WRITE setl1Button NOTIFY l1ButtonChanged);
    float l1Button() const;
    virtual void setl1Button(float value);

    Q_PROPERTY(float l2Button READ l2Button WRITE setl2Button NOTIFY l2ButtonChanged);
    float l2Button() const;
    virtual void setl2Button(float value);

    Q_PROPERTY(float r1Button READ r1Button WRITE setl1Button NOTIFY r1ButtonChanged);
    float r1Button() const;
    virtual void setr1Button(float value);

    Q_PROPERTY(float r2Button READ r2Button WRITE setr2Button NOTIFY r2ButtonChanged);
    float r2Button() const;
    virtual void setr2Button(float value);

    Q_PROPERTY(float axisButton READ axisButton WRITE setaxisButton NOTIFY axisButtonChanged);
    float axisButton() const;
    virtual void setaxisButton(float value);

    Q_PROPERTY(float xAxis READ xAxis WRITE setxAxis NOTIFY xAxisChanged);
    float xAxis() const;
    virtual void setxAxis(float value);

    Q_PROPERTY(float yAxis READ yAxis WRITE setxAxis NOTIFY yAxisChanged);
    float yAxis() const;
    virtual void setyAxis(float value);

    Q_PROPERTY(float axis2Button READ axis2Button WRITE setaxis2Button NOTIFY axis2ButtonChanged);
    float axis2Button() const;
    virtual void setaxis2Button(float value);

    Q_PROPERTY(float xAxis2 READ xAxis2 WRITE setxAxis2 NOTIFY xAxis2Changed);
    float xAxis2() const;
    virtual void setxAxis2(float value);

    Q_PROPERTY(float yAxis2 READ yAxis2 WRITE setxAxis2 NOTIFY yAxis2Changed);
    float yAxis2() const;
    virtual void setyAxis2(float value);

    QHash<int,QByteArray> roleNames() const override {return QHash<int,QByteArray>();};
    int rowCount(const QModelIndex & /*parent = QModelIndex()*/) const override {return 0;};
    QVariant data(const QModelIndex &/*index*/, int /*role = Qt::DisplayRole*/) const override{return QVariant();};


    void onButtonDown(FSDeviceInputEvent event) override;
    void onButtonUp(FSDeviceInputEvent event) override;
    void onStickMove(FSDeviceInputEvent event) override;


signals:
    void joystickIDChanged(int newID);
    void upDpadChanged(float value);
    void downDpadChanged(float value);
    void leftDpadChanged(float value);
    void rightDpadChanged(float value);
    void aButtonChanged(float value);
    void bButtonChanged(float value);
    void xButtonChanged(float value);
    void yButtonChanged(float value);
    void centerButtonChanged(float value);
    void startButtonChanged(float value);
    void selectButtonChanged(float value);
    void l1ButtonChanged(float value);
    void l2ButtonChanged(float value);
    void r1ButtonChanged(float value);
    void r2ButtonChanged(float value);
    void axisButtonChanged(float value);
    void xAxisChanged(float value);
    void yAxisChanged(float value);
    void axis2ButtonChanged(float value);
    void xAxis2Changed(float value);
    void yAxis2Changed(float value);
protected:
    void updateControllerValues(FSDeviceInputEvent & event,bool pressed);
    void updateModel(unsigned int joystickiD);

private:
    unsigned int m_joystickId = -1;
    float m_upDpad = 0.0f;
    float m_downDpad = 0.0f;
    float m_leftDpad = 0.0f;
    float m_rightDpad = 0.0f;
    float m_aButton = 0.0f;
    float m_bButton = 0.0f;
    float m_xButton = 0.0f;
    float m_yButton = 0.0f;
    float m_centerButton = 0.0f;
    float m_l1Button = 0.0f;
    float m_l2Button = 0.0f;
    float m_r1Button = 0.0f;
    float m_r2Button = 0.0f;
    float m_startButton = 0.0f;
    float m_selectButton = 0.0f;
    float m_axisButton = 0.0f;
    float m_xAxis = 0.0f;
    float m_axis2Button = 0.0f;
    float m_yAxis = 0.0f;
    float m_xAxis2 = 0.0f;
    float m_yAxis2 = 0.0f;
};

