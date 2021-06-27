import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

Item {
    id: controller
    width: 900
    height: 600
    property alias rightSholderButtons: rightSholderButtons
    property alias leftSholderButtons: leftSholderButtons
    property alias centerButtons: centerButtons
    property alias dpadButtons: dpadButtons
    property alias contollerRightAxis: contollerRightAxis
    property alias contollerLeftAxis: contollerLeftAxis
    property alias xyabControl: faceButtons
    Page {
        id: page
        anchors.fill: parent
        RowLayout {
            anchors.fill: parent
            Rectangle {
                color: "#E5E5E5"
                Layout.preferredHeight: 100
                Layout.preferredWidth: controller.width * 0.25
                Layout.minimumWidth: 200
                Layout.minimumHeight: 100
                Layout.fillHeight: true
                RowLayout {
                    id: axisRow
                    anchors.fill: parent
                    ContollerAxis {
                        id: contollerLeftAxis
                        Layout.fillWidth: true
                        Layout.maximumHeight: width
                        Layout.preferredHeight: width
                        color: "black"
                    }

                    ContollerAxis {
                        id: contollerRightAxis
                        Layout.fillWidth: true
                        Layout.maximumHeight: width
                        Layout.preferredHeight: width
                        color: "black"
                    }
                }
            }
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                RowLayout {
                    id: sholderRow
                    property real childSizeSholder: controller.width * 0.75 / 6
                    Layout.preferredWidth: controller.width * 0.75
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    SholderButtons {
                        id: leftSholderButtons
                        topButton.buttonText.text: "L2"
                        bottomButton.buttonText.text: "L1"
                        Layout.preferredHeight: 100
                        Layout.preferredWidth: sholderRow.childSizeSholder
                    }
                    Rectangle {
                        Layout.preferredHeight: 107
                        Layout.preferredWidth: sholderRow.childSizeSholder * 3.5
                        // color: "transparent"
                    }

                    SholderButtons {
                        id: rightSholderButtons
                        Layout.preferredHeight: 107
                        Layout.preferredWidth: sholderRow.childSizeSholder
                        topButton.buttonText.text: "R2"
                        bottomButton.buttonText.text: "R1"
                    }
                }

                RowLayout {
                    id: buttonRow

                    property real childSize: controller.width * 0.70 / 3
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    ContorllerDpadButtons {
                        id: dpadButtons
                        //Layout.preferredWidth: buttonRow.childSize
                        // Layout.preferredHeight: buttonRow.childSize
                        Layout.fillWidth: true
                        Layout.maximumHeight: width
                        Layout.preferredHeight: width
                    }
                    ContollerCenterButtons {
                        id: centerButtons
                        // Layout.preferredWidth: buttonRow.childSize
                        //Layout.preferredHeight: buttonRow.childSize
                        Layout.fillWidth: true
                        Layout.maximumHeight: width
                        Layout.preferredHeight: width
                    }

                    ControllerFourButtons {
                        id: faceButtons
                        //Layout.fillHeight: false
                        // Layout.fillWidth: false
                        //Layout.preferredWidth: buttonRow.childSize
                        //Layout.preferredHeight: buttonRow.childSize
                        Layout.fillWidth: true
                        Layout.maximumHeight: width
                        Layout.preferredHeight: width
                    }
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

