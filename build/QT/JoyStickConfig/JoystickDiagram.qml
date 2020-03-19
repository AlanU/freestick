import QtQuick 2.4
import org.freestick.models 1.0

JoystickDiagramForm {
    property int currentInfoPageControllerID: 0
    onCurrentInfoPageControllerIDChanged: {
        controllerDiagramModel.joystickID = currentControllerID
    }
    ControllerDiagram {
       id:controllerDiagramModel
       manager: deviceManager
       function updateButton(button,value)
       {
            button.button.color = value > 0 ? "red" : "green"
       }

       onAButtonChanged: {
           updateButton(xyabControl.aButton,value)
       }

       onBButtonChanged: {
           updateButton(xyabControl.bButton,value)
       }

       onXButtonChanged:
       {
           updateButton(xyabControl.xButton,value)
       }

       onYButtonChanged: {
           updateButton(xyabControl.yButton,value)
       }
    }

}
