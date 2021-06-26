import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

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
        RowLayout {
            anchors.fill: parent
            RowLayout {
                Layout.maximumWidth: 200
                Layout.maximumHeight: 100
                Layout.preferredHeight: 100
                Layout.preferredWidth: 200

                ContollerAxis {
                    id: contollerLeftAxis
                    Layout.preferredHeight: 100
                    Layout.preferredWidth: 100
                    color: "black"
                }

                ContollerAxis {
                    id: contollerRightAxis
                    Layout.preferredHeight: 100
                    Layout.preferredWidth: 100
                    color: "black"
                }
                Layout.fillHeight: true
                Layout.preferredWidth: 200
            }
            RowLayout {
                ContorllerDpadButtons {
                    id: dpadButtons
                    width: 200
                    height: 200
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 200
                }

                ControllerXYABButtons {
                    id: thumbButtons
                    x: 575
                    y: 137
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 200
                }

                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
