import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: controller
    width: 600
    height: 600
    property alias dpadButtons: dpadButtons
    property alias contollerRightAxis: contollerRightAxis
    property alias contollerLeftAxis: contollerLeftAxis
    property alias xyabControl: thumbButtons
    Page {
        id: page
        height: 400
        anchors.fill: parent
        ContorllerDpadButtons {
            id: dpadButtons
            x: 0
            y: 137
            width: 200
            height: 200
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.rightMargin: 10
        }

        ControllerXYABButtons {
            id: thumbButtons
            x: 575
            y: 137
            width: 200
            height: 200
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
        }

        ContollerAxis {
            id: contollerLeftAxis
            y: 400
            width: 100
            height: 100
            color: "black"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 214
            anchors.bottomMargin: 100

        }

        ContollerAxis {
            id: contollerRightAxis
            x: 340
            y: 400
            width: 100
            height: 100
            color: "black"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
        }
    }
}
