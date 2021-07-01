import QtQuick 2.9
import QtQuick.Controls 2.12
import org.freestick.models 1.0

ApplicationWindow {
    id: window
    width: 900
    height: 600
    visible: true
    title: "Joystick Config"
    minimumWidth: 900
    minimumHeight: 600
    MainForm {
        id:main
        anchors.fill: parent
        deviceModel: DeviceList{
                         id:deviceModelList
                         manager: deviceManager
                         onModelReset: {
                            if (main.devicesControl.currentText === "")
                            {
                                main.devicesControl.currentIndex = 0
                            }
                         }
                     }
        devicesControl.onCurrentIndexChanged: {
            let id = deviceModelList.getIdFromIndex(devicesControl.currentIndex)
            if(id)
            {
                currentControllerID = id

            }
        }

        tabBar.onCurrentIndexChanged: {
            swipeView.setCurrentIndex(tabBar.currentIndex)
        }
    }


}
