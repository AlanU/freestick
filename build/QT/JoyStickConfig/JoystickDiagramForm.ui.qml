import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

Item {
    id: controller
    width: 900
    height: 600
    property alias centerButtons: centerButtons
    property alias dpadButtons: dpadButtons
    property alias contollerRightAxis: contollerRightAxis
    property alias contollerLeftAxis: contollerLeftAxis
    property alias xyabControl: faceButtons
    Page {
        id: page
        height: 400
        anchors.fill: parent
        RowLayout {
            anchors.fill: parent
            RowLayout {
                id: axisRow
                property real childSize: (controller.width * 0.30) / 2
                Layout.preferredHeight: 100
                Layout.preferredWidth: 200
                Layout.maximumWidth: controller.width * 0.30
                Layout.minimumWidth: 200
                Layout.minimumHeight: 100
                Layout.fillHeight: true

                ContollerAxis {
                    id: contollerLeftAxis
                    Layout.preferredHeight: axisRow.childSize
                    Layout.preferredWidth: axisRow.childSize
                    Layout.maximumHeight: axisRow.childSize
                    Layout.maximumWidth: axisRow.childSize
                    color: "black"
                }

                ContollerAxis {
                    id: contollerRightAxis
                    Layout.preferredHeight: axisRow.childSize
                    Layout.preferredWidth: axisRow.childSize
                    Layout.maximumHeight: axisRow.childSize
                    Layout.maximumWidth: axisRow.childSize
                    color: "black"
                }
            }
            RowLayout {
                id: buttonRow

                property real childSize: controller.width * 0.70 / 3
                Layout.fillWidth: true
                Layout.fillHeight: true
                ContorllerDpadButtons {
                    id: dpadButtons
                    Layout.preferredWidth: buttonRow.childSize
                    Layout.preferredHeight: buttonRow.childSize
                }
                ContollerCenterButtons {
                    id: centerButtons
                    Layout.preferredWidth: buttonRow.childSize
                    Layout.preferredHeight: buttonRow.childSize
                }

                ControllerFourButtons {
                    id: faceButtons
                    //Layout.fillHeight: false
                    // Layout.fillWidth: false
                    Layout.preferredWidth: buttonRow.childSize
                    Layout.preferredHeight: buttonRow.childSize
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/

