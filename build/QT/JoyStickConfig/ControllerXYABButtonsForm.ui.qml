import QtQuick 2.4

Item {
    id: element
    width: 100
    height: 100
    property alias bButton: bButton
    property alias xButton: xButton
    property alias yButton: yButton
    property alias aButton: aButton
    ControllerButton {
        id: yButton
        x: 150
        width: element.width / 4
        height: width
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        buttonText.text: "Y"
    }

    ControllerButton {
        id: aButton
        x: 150
        y: 235
        width: element.width / 4
        height: width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: yButton.horizontalCenter
        buttonText.text: "A"
    }

    ControllerButton {
        id: xButton
        y: 133
        width: element.width / 4
        height: width
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
        buttonText.text: "X"
    }

    ControllerButton {
        id: bButton
        x: 273
        y: 133
        width: element.width / 4
        height: width
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: xButton.verticalCenter
        buttonText.text: "B"
    }
}

/*##^##
Designer {
    D{i:1;anchors_y:52}D{i:3;anchors_x:23}
}
##^##*/

