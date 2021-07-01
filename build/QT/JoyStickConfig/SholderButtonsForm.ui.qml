import QtQuick 2.4
import QtQuick.Layouts 1.11

Item {
    id: root
    width: 108
    height: 62
    property alias bottomButton: bottomButton
    property alias topButton: topButton
    property real buttonWidth: 150
    property real buttonHeight: 50
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        property real buttonWidth: root.width / 2
        ControllerButton {
            id: topButton
            Layout.fillWidth: true
            Layout.fillHeight: true
            rounded: false
            Layout.maximumHeight: width/3
        }

        ControllerButton {
            id: bottomButton
            Layout.fillWidth: true
            Layout.fillHeight: true
            rounded: false
            Layout.maximumHeight: width/3
        }
    }
}
