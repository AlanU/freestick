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
       function updateAnlogBars(elementBar,value){
            let finalValue = value
           if(elementBar.precent === false) {
              finalValue  = Math.floor((value + Number.EPSILON) * 10000) / 10000
           }
           elementBar.value = finalValue
       }

       function updateAxisButton(axisObj,value)
       {
           axisObj.button.color = value > 0 ? "green" : "#EEEEEE"
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
           updateAxisButton(l3,value)
       }
       onXAxisChanged: {
           updateAxis(contollerLeftAxis,value,true)
           updateAnlogBars(xAxis1Bar,value)
       }
       onYAxisChanged: {
           updateAxis(contollerLeftAxis,value,false)
           updateAnlogBars(yAxis1Bar,value)
       }
       onAxis2ButtonChanged: {
           updateAxisButton(r3,value)
       }
       onXAxis2Changed: {
           updateAxis(contollerRightAxis,value,true)
           updateAnlogBars(xAxis2Bar,value)

       }
       onYAxis2Changed: {
           updateAxis(contollerRightAxis,value,false)
           updateAnlogBars(yAxis2Bar,value)
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
       onLeftTriggerChanged: {
           updateAnlogBars(rigthSholderBar,value)
       }
       onRightTriggerChanged: {
           updateAnlogBars(leftSholderBar,value)
       }

    }

}
