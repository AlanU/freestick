import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: controller
    width: 600
    height: 600
    property alias xyabControl: thumbButtons
    Page {
        id: page
        height: 400
        anchors.fill: parent
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
    }
}
