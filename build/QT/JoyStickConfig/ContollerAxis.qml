import QtQuick 2.4

ContollerAxisForm {
    property string buttonColor: "green"
    property string color: "white"

    function setButtonColor(newColor){
        stick.color = newColor
    }

    function setColor(newColor){
        axis.color = newColor
    }

    function convertNormalizedRangerToAxisPoint(value, maxValue, minValue)
    {
        let joystickRange =  2;
        let libRange = maxValue - minValue;
        let newNormilzedValue =  ( (( (value) - (-1)) * libRange)/joystickRange ) + minValue ;
        return  newNormilzedValue;

    }
    function setAxisWidgetFromValue(value,setX)
    {
        let valueForPoint = convertNormalizedRangerToAxisPoint(value,axis.width,0);

        if(setX)
            stick.x = valueForPoint-stick.width/2
        else
            stick.y = valueForPoint-(stick.height/2)
    }
    Component.onCompleted: {
        setColor(color)
        setButtonColor(buttonColor)
        stick.x =  (axis.width/2) - (stick.width/2)
        stick.y =  (axis.height/2) - (stick.height/2)
    }

    onColorChanged: {
        setColor(color)
    }

    onButtonColorChanged: {
        setButtonColor(buttonColor)
    }

}
