import QtQuick 2.4
import org.freestick.models 1.0
JoystickTablePageForm {
    model:ContorllerMapping{
           id:controllerModel
          manager: deviceManager
    }
    deviceModel: DeviceList{
        id:deviceModelList
        manager: deviceManager
        onModelReset: {
            if (devicesControl.currentText == "")
            {
                devicesControl.currentIndex = 0
            }
        }
    }
    devicesControl.onCurrentIndexChanged: {
        let id = deviceModelList.getIdFromIndex(devicesControl.currentIndex)
        controllerModel.joystickID = id
    }
}
