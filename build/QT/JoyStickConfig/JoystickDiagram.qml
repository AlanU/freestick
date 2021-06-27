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
            button.button.color = value > 0 ? "green" : "#EEEEEE"
       }

       function updateAxis(axis, value, xAxis){
           axis.setAxisWidgetFromValue(value,xAxis)
       }
       function updateAxisButton(axisObj,value)
       {
           axisObj.buttonColor = value > 0 ? "green" : "#EEEEEE"
       }
       onUpDpadChanged: {
           updateButton(dpadButtons.yButton,value)
       }
       onDownDpadChanged: {
           updateButton(dpadButtons.aButton,value)
       }
       onLeftDpadChanged: {
           updateButton(dpadButtons.xButton,value)
       }
       onRightDpadChanged: {
           updateButton(dpadButtons.bButton,value)
       }
       onAButtonChanged: {
           updateButton(xyabControl.aButton,value)
       }
       onBButtonChanged: {
           updateButton(xyabControl.bButton,value)
       }
       onXButtonChanged:{
           updateButton(xyabControl.xButton,value)
       }
       onYButtonChanged: {
           updateButton(xyabControl.yButton,value)
       }
       onCenterButtonChanged: {
           updateButton(centerButtons.aButton,value)
       }
       onStartButtonChanged: {
           updateButton(centerButtons.bButton,value)
       }
       onSelectButtonChanged: {
           updateButton(centerButtons.xButton,value)
       }
       onAxisButtonChanged: {
           updateAxisButton(contollerLeftAxis,value)
       }
       onXAxisChanged: {
           updateAxis(contollerLeftAxis,value,true)
       }
       onYAxisChanged: {
           updateAxis(contollerLeftAxis,value,false)
       }
       onAxis2ButtonChanged: {
           updateAxisButton(contollerRightAxis,value)
       }
       onXAxis2Changed: {
           updateAxis(contollerRightAxis,value,true)
       }
       onYAxis2Changed: {
           updateAxis(contollerRightAxis,value,false)
       }
       onL1ButtonChanged: {
           updateButton(leftSholderButtons.bottomButton,value)
       }
       onL2ButtonChanged: {
           updateButton(leftSholderButtons.topButton,value)
       }
       onR1ButtonChanged: {
           updateButton(rightSholderButtons.bottomButton,value)
       }
       onR2ButtonChanged: {
           updateButton(rightSholderButtons.topButton,value)
       }

    }

}
