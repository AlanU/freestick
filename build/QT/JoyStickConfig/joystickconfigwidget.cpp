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
using namespace freestick;
JoyStickConfigWidget::JoyStickConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JoyStickConfigWidget)
{
    ui->setupUi(this);


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
    ui->DeviceID->hide();
    ui->FoceFeedBack->hide();
    timer= new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000);
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
}

void JoyStickConfigWidget::onButtonDown(FSDeviceInputEvent event)
{
   // if(!isCurrentDevice(event.getDeviceID()))
   //     return;

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
}

 void JoyStickConfigWidget::onButtonUp(FSDeviceInputEvent event)
{
     //if(!isCurrentDevice(event.getDeviceID()))
     //    return;

     QString text;
     if(FS_isDpad(event.getInputType()) )
     {
          text = tr("DPad ");
          if(event.getInputType()== DPadLeft)
          {
              ui->tabWidget->setCurrentIndex(0);
          }
          else if(event.getInputType() == DPadRight)
          {
              ui->tabWidget->setCurrentIndex(1);
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

}
void JoyStickConfigWidget::onConnect(FSBaseEvent event)
{
    qDebug()<<"Event Type "<<event.getEventType()<<" ID "<<event.getDeviceID()<<" time stamp "<<event.getTimeStamp()<<endl;
    const FSBaseDevice * device = deviceManager.getDevice(event.getDeviceID());
    QString deviceBoxName = tr(device->GetFrendlyName().c_str());
    ui->DeviceListBox->addItem(deviceBoxName,event.getDeviceID());
    PopulateDeviceStats(ui->DeviceListBox->itemData(ui->DeviceListBox->currentIndex()).toUInt());

}

void JoyStickConfigWidget::update()
{
    //deviceManager.update();
}

void JoyStickConfigWidget::onDisconnect(FSBaseEvent event)
{
    qDebug()<<"Event Type "<<event.getEventType()<<" ID "<<event.getDeviceID()<<" time stamp "<<event.getTimeStamp()<<endl;
    int index = ui->DeviceListBox->findData(event.getDeviceID(),int(Qt::UserRole));
    if(index != -1)
    {
        ui->DeviceListBox->removeItem(index);
    }


}

void JoyStickConfigWidget::PopulateDeviceStats(unsigned int id)
{
   const FSBaseDevice * device = deviceManager.getDevice(id);
   bool FFBackSupport = false;
   if(device == NULL)
   {
         ui->DeviceID->hide();
         ui->FoceFeedBack->hide();
         return;
   }

   QString DeviceInfo = "Device ID: ";
   DeviceInfo +=  QString::number(device->getJoystickID());

    if(device != NULL && device->getClassType() >= FSUSBJoystickType)
    {
      const  FSUSBJoystick * usbDevice = (const FSUSBJoystick *) device;

      DeviceInfo += " Number of Buttons: ";
      DeviceInfo += QString::number(usbDevice->getNumberOfButtons());

      DeviceInfo += " Number of Anolg Sticks: ";
      DeviceInfo += QString::number(usbDevice->getNumberOfAnlogSticks());

      DeviceInfo += " Number of Digital Sticks: ";
      DeviceInfo += QString::number(usbDevice->getNumberOfDigitalSticks());
      FFBackSupport = usbDevice->getForceFeedbackSupport();
      \

    }
     ui->FoceFeedBack->setChecked(FFBackSupport);
     ui->DeviceID->setText(DeviceInfo);
     ui->DeviceID->show();
     ui->FoceFeedBack->show();
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
}
