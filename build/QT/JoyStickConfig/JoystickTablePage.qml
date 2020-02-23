import QtQuick 2.4
import org.freestick.models 1.0
JoystickTablePageForm {
    property int currentTableContorllerID: -1

    model:ContorllerMapping{
          id:controllerModel
          manager: deviceManager
          onJoystickIDChanged:
          {
                console.log(joystickID)
          }
    }
    onCurrentTableContorllerIDChanged: {
        controllerModel.joystickID =currentTableContorllerID
    }

}
