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

#ifndef JOYSTICKCONFIGWIDGET_H
#define JOYSTICKCONFIGWIDGET_H

#include <QWidget>
#include <QTimer>

#include "freestick.h"
#include "controllermappingtablemodel.h"
namespace Ui {
class JoyStickConfigWidget;
}

class JoyStickConfigWidget : public QWidget , public freestick::IFSJoystickListener
{
    Q_OBJECT

public:
    explicit JoyStickConfigWidget(QWidget *parent = 0);
    ~JoyStickConfigWidget();
    virtual void onButtonDown(freestick::FSDeviceInputEvent event);
    virtual void onButtonUp(freestick::FSDeviceInputEvent event) ;
    virtual void onStickMove(freestick::FSDeviceInputEvent event);
    virtual void onDisconnect(freestick::FSBaseEvent event);
    virtual void onConnect(freestick::FSBaseEvent event);
    bool isCurrentDevice(unsigned int device);
public slots:
    void update();
private slots:
    void on_DeviceListBox_currentIndexChanged(int index);

private:
    /** \todo
     *put device manager more centrlized
     */
    FreeStickDeviceManager deviceManager;
    Ui::JoyStickConfigWidget *ui;
    void PopulateDeviceStats(unsigned int id);
    QTimer * timer;
    void updateVirtualDigitalGamePad(freestick::FSDeviceInput input,freestick::FSEventAction action );
    void updateVirtualAnalogGamePad(freestick::FSDeviceInput input,freestick::FSEventAction action,float value );
    void updateVirtualButton(QWidget * button,freestick::FSEventAction action );
    void updateVirtualButton(QWidget * button,freestick::FSEventAction action,QColor buttonColor,QColor releaseButtonColor );
    float convertNormalizedRangerToAxisPoint(float value,int maxValue,int minValue);
    void setAxisWidgetFromValue(QWidget * widgetToSet,float value,bool setX);
    std::map<unsigned int ,ControllerMappingTableModel *> _joystickModelMap;


};

#endif // JOYSTICKCONFIGWIDGET_H
