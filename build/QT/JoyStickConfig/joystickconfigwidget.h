#ifndef JOYSTICKCONFIGWIDGET_H
#define JOYSTICKCONFIGWIDGET_H

#include <QWidget>
#include "../../../src/Interfaces/IFSJoystickListener.h"
#include "../../../src/USB/platform/NULL/FSUSBNullJoystickDeviceManager.h"

#include <QTimer>
using namespace freestick;
#ifdef __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
        // define something for simulator
        typedef FSUSBNullJoystickDeviceManager JoystickManager;
    #elif TARGET_OS_IPHONE
        // define something for iphone
        typedef FSUSBNullJoystickManager JoystickManager;
    #else
        #define TARGET_OS_OSX 1
        // define something for OSX
        #include "../../../src/USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.h"
        typedef FSUSBMacOSXJoystickDeviceManager JoystickManager;
    #endif
#elif __ANDROID__
    //define for android
    #include "../../../src/USB/platform/Android/FSHIDAndroidJoysickDeviceManager.h"
typedef FSHIDAndroidJoysickDeviceManager JoystickManager;

#else
    typedef FSUSBNullJoystickManager JoystickManager;
#endif


namespace Ui {
class JoyStickConfigWidget;
}

class JoyStickConfigWidget : public QWidget , public IFSJoystickListener
{
    Q_OBJECT

public:
    explicit JoyStickConfigWidget(QWidget *parent = 0);
    ~JoyStickConfigWidget();
    virtual void OnButtonDown(FSDeviceInputEvent event);
    virtual void OnButtonUp(FSDeviceInputEvent event) ;
    virtual void OnStickMove(FSDeviceInputEvent event);
    virtual void OnDisconnect(FSBaseEvent event);
    virtual void OnConnect(FSBaseEvent event);
    bool isCurrentDevice(unsigned int device);
public slots:
    void update();
private slots:
    void on_DeviceListBox_currentIndexChanged(int index);

private:
    /** \todo
     *put device manager more centrlized
     */
    JoystickManager deviceManager;
    Ui::JoyStickConfigWidget *ui;
    void PopulateDeviceStats(unsigned int id);
    QTimer * timer;
};

#endif // JOYSTICKCONFIGWIDGET_H
