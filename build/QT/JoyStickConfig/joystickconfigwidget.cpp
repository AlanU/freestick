#include "joystickconfigwidget.h"
#include "ui_joystickconfigwidget.h"
#include "../../../src/baseClasses/FSBaseDevice.h"
#include "../../../src/USB/FSUSBJoystick.h"
#include "../../../src/FSDeviceInputEvent.h"
#include <iostream>
#include <QTimer>

JoyStickConfigWidget::JoyStickConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JoyStickConfigWidget)
{
    ui->setupUi(this);

    deviceManager.init();
    deviceManager.ListenForJoystickConnection(*this);
    deviceManager.ListenForJoystickDisconnections(*this);
    deviceManager.ListenForAllJoysticksForEventType(FS_BUTTON_EVENT,*this);
    deviceManager.ListenForAllJoysticksForEventType(FS_AXIS_EVENT,*this);
    deviceManager.ListenForAllJoysticksForEventType(FS_TRIGGER_EVENT,*this);
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

void JoyStickConfigWidget::OnStickMove(FSDeviceInputEvent event)
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

void JoyStickConfigWidget::OnButtonDown(FSDeviceInputEvent event)
{
    if(!isCurrentDevice(event.getDeviceID()))
        return;

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

 void JoyStickConfigWidget::OnButtonUp(FSDeviceInputEvent event)
{
     if(!isCurrentDevice(event.getDeviceID()))
         return;

     QString text;
     if(FS_isDpad(event.getInputType()) )
     {
          text = tr("DPad ");
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
void JoyStickConfigWidget::OnConnect(FSBaseEvent event)
{
    std::cout<<"Event Type "<<event.getEventType()<<" ID "<<event.getDeviceID()<<" time stamp "<<event.getTimeStamp()<<std::endl;
    const FSBaseDevice * device = deviceManager.getDevice(event.getDeviceID());
    QString deviceBoxName = tr(device->GetFrendlyName().c_str());
    ui->DeviceListBox->addItem(deviceBoxName,event.getDeviceID());
    PopulateDeviceStats(ui->DeviceListBox->itemData(ui->DeviceListBox->currentIndex()).toUInt());

}

void JoyStickConfigWidget::update()
{
    //deviceManager.update();
}

void JoyStickConfigWidget::OnDisconnect(FSBaseEvent event)
{
    std::cout<<"Event Type "<<event.getEventType()<<" ID "<<event.getDeviceID()<<" time stamp "<<event.getTimeStamp()<<std::endl;
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
