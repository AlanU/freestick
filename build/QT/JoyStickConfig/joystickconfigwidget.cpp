/**************************************************************************
Created by Alan Uthoff on 10/8/2013
Copyright (C) 2013.

This Code is free software; you can redistribute it and/or
modify it under the terms of the zlib/libpng License as published
by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
**************************************************************************/

#include "joystickconfigwidget.h"
#include "ui_joystickconfigwidget.h"
#include <QTimer>
#include <QDebug>
#ifdef Q_OS_ANDROID
#include <QAndroidJniEnvironment>
#endif

#include "controllermappingtablemodel.h"
using namespace freestick;
JoyStickConfigWidget::JoyStickConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JoyStickConfigWidget)
{
    ui->setupUi(this);

    ui->tab_3->setWindowTitle("Virtual Control");
#ifdef Q_OS_ANDROID
    QAndroidJniEnvironment qjniEnv;
    JavaVM * jvm = QAndroidJniEnvironment::javaVM();
    deviceManager.init(jvm);

#else
     deviceManager.init();
#endif
    deviceManager.ListenForAllJoysticksForEventTypes(FS_JOYSTICK_CONNECTED_EVENT |
                                                     FS_JOYSTICK_DISCONNECT_EVENT |
                                                     FS_BUTTON_EVENT | FS_AXIS_EVENT
                                                     | FS_TRIGGER_EVENT,*this);
    ui->deviceID->hide();
    ui->FoceFeedBack->hide();
    timer= new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
#ifdef Q_OS_WIN32
    timer->start(100);
#else
    timer->start(1000);
#endif
    QPalette buttonPressed(palette());
    buttonPressed.setColor(QPalette::Background,Qt::black);
    ui->RightStickPoint->setAutoFillBackground(true);
    ui->RightStickPoint->setPalette(buttonPressed);
    ui->LeftStickPoint->setAutoFillBackground(true);
    ui->LeftStickPoint->setPalette(buttonPressed);

    QPalette axisBackgroud(palette());
    axisBackgroud.setColor(QPalette::Background,Qt::white);
    ui->RightStick->setAutoFillBackground(true);
    ui->RightStick->setPalette(axisBackgroud);

    ui->LeftStick->setAutoFillBackground(true);
    ui->LeftStick->setPalette(axisBackgroud);
}

JoyStickConfigWidget::~JoyStickConfigWidget()
{
    delete timer;
    delete ui;
}

bool JoyStickConfigWidget::isCurrentDevice(unsigned int device)
{
  return (ui->DeviceListBox->currentData().toUInt() == device ) ? true : false;

}

void JoyStickConfigWidget::onStickMove(FSDeviceInputEvent event)
{
    if(!isCurrentDevice(event.getDeviceID()))
        return;

    QString text;
    if(FS_isAxis(event.getInputType()))
    { 
         text = tr("Axise ");
    }
    else if(FS_isTrigger(event.getInputType()))
    {
         text = tr("Trigger ");

    }
    text += tr("Changed for device ");
    text += QString::number(event.getDeviceID());
    text += tr(" with AnologID ");
    text += QString::number(event.getControlID());
    text += tr(" with Value of ");
    text += QString::number(event.getNewInputValue());
    ui->AnologDebugControl->setText(text);
    updateVirtualAnalogGamePad(event.getInputType(),event.getEventAction(),event.getNewInputValue() );

}
void JoyStickConfigWidget::updateVirtualButton(QWidget * button,freestick::FSEventAction action )
{
    updateVirtualButton(button,action,Qt::red,Qt::blue);
}

void JoyStickConfigWidget::updateVirtualButton(QWidget * button,FSEventAction action ,QColor buttonColor,QColor releaseButtonColor )
{
    QPalette buttonPressed(palette());
    buttonPressed.setColor(QPalette::Background,buttonColor);
    if(action == FSInputPressed)
    {
       button->setAutoFillBackground(true);
        button->setPalette(buttonPressed);
    }
    else if(releaseButtonColor != Qt::transparent)
    {
        QPalette buttonRelease(palette());
        buttonRelease.setColor(QPalette::Background,releaseButtonColor);
        button->setAutoFillBackground(true);
         button->setPalette(buttonRelease);
    }
    else
    {
        button->setAutoFillBackground(false);

    }
}

void JoyStickConfigWidget::setAxisWidgetFromValue(QWidget * widgetToSet,float value,bool setX)
{
    float valueForPoint = convertNormalizedRangerToAxisPoint(value,widgetToSet->parentWidget()->width(),0);

    if(setX)
        widgetToSet->setGeometry(valueForPoint-widgetToSet->width()/2,widgetToSet->y(),widgetToSet->width(),widgetToSet->height());
    else
        widgetToSet->setGeometry(widgetToSet->x(), valueForPoint-(widgetToSet->height()/2),widgetToSet->width(),widgetToSet->height());

}

void JoyStickConfigWidget::updateVirtualAnalogGamePad(FSDeviceInput input,FSEventAction action,float value )
{
    action;//to remove unused warning
    switch (input)
    {
        case Trigger1:
            ui->LeftTrigger->setValue(value*100);
        break;
        case Trigger2:
            ui->RightTrigger->setValue(value*100);
        break;
        case XAxis:
           setAxisWidgetFromValue(ui->RightStickPoint,value,true);
           ui->LeftStickXBar->setValue(value*100);
        break;
        case YAxis:
            setAxisWidgetFromValue(ui->RightStickPoint,value,false);
            ui->LeftStickYBar->setValue(value*100);
        break;
        case XAxis2:
          setAxisWidgetFromValue(ui->LeftStickPoint,value,true);
          ui->RightStickXBar->setValue(value*100);
        break;
        case YAxis2:
            setAxisWidgetFromValue(ui->LeftStickPoint,value,false);
            ui->RightStickYBar->setValue(value*100);
        break;
        default:
        break;

    }
}
void JoyStickConfigWidget::updateVirtualDigitalGamePad(FSDeviceInput input,FSEventAction action )
{

    switch (input)
    {
        case DPadDown:
           updateVirtualButton(ui->dpadDown,action);
        break;
        case DPadUp:
            updateVirtualButton(ui->dpadUp,action);
        break;
        case DPadLeft:
            updateVirtualButton(ui->dpadLeft,action);
        break;
        case DPadRight:
            updateVirtualButton(ui->dpadRight,action);
        break;
        case ButtonX:
            updateVirtualButton(ui->ButtonX,action);
        break;
        case ButtonY:
            updateVirtualButton(ui->ButtonY,action);
        break;
        case ButtonA:
            updateVirtualButton(ui->ButtonA,action);
        break;
        case ButtonB:
            updateVirtualButton(ui->ButtonB,action);
        break;
        case ButtonSelect:
            updateVirtualButton(ui->SelectButton,action);
        break;
        case ButtonStart:
            updateVirtualButton(ui->StartButton,action);
        break;
        case LeftShoulder:
            updateVirtualButton(ui->L1,action);
        break;
        case RightShoulder:
            updateVirtualButton(ui->R1,action);
        break;
        case LeftShoulder2:
            updateVirtualButton(ui->L2,action);
        break;
        case RightShoulder2:
            updateVirtualButton(ui->R2,action);
        break;
        case Button10:
            updateVirtualButton(ui->RightStickPoint,action,Qt::red,Qt::black);
        break;
        case Button11:
            updateVirtualButton(ui->LeftStickPoint,action,Qt::red,Qt::black);
        break;
        case ButtonCenter:
            updateVirtualButton(ui->CenterButton,action);
        break;
        default:
            break;
    }
}

void JoyStickConfigWidget::onButtonDown(FSDeviceInputEvent event)
{
    if(!isCurrentDevice(event.getDeviceID()))
        return;

    qDebug()<<"button down"<<endl;
    QString text;
    if(FS_isDpad(event.getInputType()) )
    {
         text = tr("DPad ");
    }
    else if(FS_isButtion(event.getInputType()))
    {
         text = tr("Button ");
    }
    text += tr("Down for device ");
    text += QString::number(event.getDeviceID());
    text += tr(" with buttonID ");
    text += QString::number(event.getControlID());
    text += tr(" with Value of ");
    text += QString::number(event.getNewInputValue());

    ui->DebugControl->setText(text);
    updateVirtualDigitalGamePad(event.getInputType(),event.getEventAction());

}

 void JoyStickConfigWidget::onButtonUp(FSDeviceInputEvent event)
{
     if(!isCurrentDevice(event.getDeviceID()))
         return;

     QString text;
     if(FS_isDpad(event.getInputType()) )
     {
          text = tr("DPad ");
          if(event.getInputType()== DPadLeft)
          {
            //  ui->tabWidget->setCurrentIndex(0);
          }
          else if(event.getInputType() == DPadRight)
          {
             // ui->tabWidget->setCurrentIndex(1);
          }

     }
     else if(FS_isButtion(event.getInputType()))
     {
          text = tr("Button ");
     }
     text += tr("Up for device");
     text += QString::number(event.getDeviceID());
     text += tr(" with buttonID ");
     text += QString::number(event.getControlID());

     ui->DebugControl->setText(text);
     updateVirtualDigitalGamePad(event.getInputType(),event.getEventAction());


}
void JoyStickConfigWidget::onConnect(FSBaseEvent event)
{
    qDebug()<<"Event Type "<<event.getEventType()<<" ID "<<event.getDeviceID()<<" time stamp "<<event.getTimeStamp()<<endl;
    const FSBaseDevice * device = deviceManager.getDevice(event.getDeviceID());
    QString deviceBoxName = tr(device->GetFrendlyName().c_str());
    ui->DeviceListBox->addItem(deviceBoxName,event.getDeviceID());
    _joystickModelMap[event.getDeviceID()] =(new ControllerMappingTableModel(deviceManager,event.getDeviceID()));
    PopulateDeviceStats(ui->DeviceListBox->itemData(ui->DeviceListBox->currentIndex()).toUInt());
   if(ui->DeviceListBox->count() == 1)
   {
    ui->Elements->setModel(  _joystickModelMap[event.getDeviceID()]);
   }

}


void JoyStickConfigWidget::update()
{
#if defined(Q_OS_WIN)

    deviceManager.update();
#endif
}

void JoyStickConfigWidget::onDisconnect(FSBaseEvent event)
{
    qDebug()<<"Event Type "<<event.getEventType()<<" ID "<<event.getDeviceID()<<" time stamp "<<event.getTimeStamp()<<endl;
    int index = ui->DeviceListBox->findData(event.getDeviceID(),int(Qt::UserRole));
    if(index != -1)
    {
        ui->DeviceListBox->removeItem(index);
    }
    if(_joystickModelMap.find(event.getDeviceID()) !=  _joystickModelMap.end())
    {
        ControllerMappingTableModel * modelToDelete = _joystickModelMap.find(event.getDeviceID())->second;
       _joystickModelMap.erase(_joystickModelMap.find(event.getDeviceID()));
        delete modelToDelete;
    }

}

void JoyStickConfigWidget::PopulateDeviceStats(unsigned int id)
{
   const FSBaseDevice * device = deviceManager.getDevice(id);
   bool FFBackSupport = false;
   if(device == NULL)
   {
         ui->deviceID->hide();
         ui->FoceFeedBack->hide();
         return;
   }

   QString DeviceInfo = "Device ID: ";
   DeviceInfo +=  QString::number(device->getJoystickID());

    if(device != NULL && device->getClassType() >= FSUSBJoystickType)
    {
      const  FSUSBJoystick * usbDevice = static_cast<const FSUSBJoystick *>(device);

        DeviceInfo += " Vendor ID: ";
        DeviceInfo += QString::number(usbDevice->getVendorID());

        DeviceInfo +=  " Product ID: ";
        DeviceInfo += QString::number(usbDevice->getProductID());


    //  DeviceInfo += " Number of Buttons: ";
   //   DeviceInfo += QString::number(usbDevice->getNumberOfButtons());

     // DeviceInfo += " Number of Anolg Sticks: ";
      //DeviceInfo += QString::number(usbDevice->getNumberOfAnlogSticks());

      //DeviceInfo += " Number of Digital Sticks: ";
     // DeviceInfo += QString::number(usbDevice->getNumberOfDigitalSticks());
      FFBackSupport = usbDevice->getForceFeedbackSupport();

    }
     ui->FoceFeedBack->setChecked(FFBackSupport);

     ui->R2->setEnabled(deviceManager.doesDeviceHaveDeviceInput(id,LeftShoulder2));
     ui->L2->setEnabled(deviceManager.doesDeviceHaveDeviceInput(id,RightShoulder2));


     ui->LeftTriggerBox->setEnabled(deviceManager.doesDeviceHaveDeviceInput(id,Trigger1));
     ui->RightTriggerBox->setEnabled(deviceManager.doesDeviceHaveDeviceInput(id,Trigger2));

     ui->deviceID->setText(DeviceInfo);
     ui->deviceID->show();
     ui->FoceFeedBack->show();
}

float JoyStickConfigWidget::convertNormalizedRangerToAxisPoint(float value,int maxValue,int minValue)
{
//taken from http://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
    double joystickRange =  2;



    double libRange = (double)maxValue - (double)minValue;


    float newNormilzedValue =  ( (( (double)value - -1) * libRange)/joystickRange ) + minValue ;
    return  newNormilzedValue;

}
void JoyStickConfigWidget::on_DeviceListBox_currentIndexChanged(int index)
{
    if(ui->DeviceListBox->count() == 0)
    {
        PopulateDeviceStats(0);
    }
    else
    {
        PopulateDeviceStats(ui->DeviceListBox->itemData(index).toUInt());
    }

    if(_joystickModelMap.find(ui->DeviceListBox->itemData(index).toUInt()) != _joystickModelMap.end())
    {
        ControllerMappingTableModel * modelToSet = _joystickModelMap[ui->DeviceListBox->itemData(index).toUInt()] ;
        ui->Elements->setModel(modelToSet);
    }

}
