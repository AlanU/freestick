import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

Item {
    id: controller
    width: 900
    height: 600
    property alias r3: r3
    property alias l3: l3
    property alias yAxis2Bar: yAxis2
    property alias yAxis1Bar: yAxis1
    property alias xAxis2Bar: xAxis2
    property alias xAxis1Bar: xAxis1
    property alias rigthSholderBar: rigthSholderProgress
    property alias leftSholderBar: leftSholderProgress
    property alias rightSholderButtons: rightSholderButtons
    property alias leftSholderButtons: leftSholderButtons
    property alias centerButtons: centerButtons
    property alias dpadButtons: dpadButtons
    property alias contollerRightAxis: contollerRightAxis
    property alias contollerLeftAxis: contollerLeftAxis
    property alias xyabControl: faceButtons
    property alias leftRoot: rectangle
    Page {
        id: page
        anchors.fill: parent
        RowLayout {
            anchors.fill: parent
            Rectangle {
                id: rectangle
                color: "#E5E5E5"
                Layout.preferredHeight: 100
                Layout.preferredWidth: controller.width * 0.25
                Layout.minimumWidth: 200
                Layout.minimumHeight: 100
                Layout.fillHeight: true
                ColumnLayout {
                    id: columnLayout
                    anchors.verticalCenter: parent.verticalCenter
                    // width: childrenRect.width
                    Layout.preferredHeight: childrenRect.height
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    anchors.leftMargin: 15

                    //anchors.fill: parent
                    spacing: 30
                    RowLayout {
                        id: shoulderRow
                        visible: leftSholderProgress.visible
                                 || rigthSholderProgress.visible
                        Layout.fillHeight: true
                        ControllerElementProgressForm {
                            id: leftSholderProgress
                            Layout.fillWidth: true
                            elemnetName: qsTr("Left Shoulder")
                            min: 0
                            max: 1
                            value: 0
                        }
                        ControllerElementProgressForm {
                            id: rigthSholderProgress
                            Layout.fillWidth: true
                            elemnetName: qsTr("Rigth Shoulder")
                            min: 0
                            max: 1
                            value: 0
                        }
                    }
                    RowLayout {
                        id: axisRow
                        Layout.fillHeight: true
                        ContollerAxis {
                            id: contollerLeftAxis
                            Layout.fillWidth: true
                            Layout.maximumHeight: width
                            Layout.preferredHeight: width
                            color: "#E5E5E5"
                            buttonColor: "red"
                            border: true
                        }

                        ContollerAxis {
                            id: contollerRightAxis
                            Layout.fillWidth: true
                            Layout.maximumHeight: width
                            Layout.preferredHeight: width
                            color: "#E5E5E5"
                            buttonColor: "red"
                            border: true
                        }
                    }
                    RowLayout {
                        id: axis1BarRow
                        Layout.fillHeight: true
                        ControllerElementProgressForm {
                            id: xAxis1
                            precent: false
                            Layout.fillWidth: true
                            elemnetName: qsTr("Axis X:")
                            min: -1
                            max: 1
                            value: 0
                        }
                        ControllerElementProgressForm {
                            id: xAxis2
                            Layout.fillWidth: true
                            precent: false
                            elemnetName: qsTr("Axis X:")
                            min: -1
                            max: 1
                            value: 0
                        }
                    }
                    RowLayout {
                        Layout.fillHeight: true
                        id: axis2BarRow
                        ControllerElementProgressForm {
                            id: yAxis1
                            Layout.fillWidth: true
                            precent: false
                            elemnetName: qsTr("Axis Y:")
                            min: -1
                            max: 1
                            value: 0
                        }
                        ControllerElementProgressForm {
                            id: yAxis2
                            Layout.fillWidth: true
                            precent: false
                            elemnetName: qsTr("Axis Y:")
                            min: -1
                            max: 1
                            value: 0
                        }
                    }
                }
            }
            ColumnLayout {
                Layout.rightMargin: 20
                Layout.leftMargin: 20
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: parent.height * 0.65
                RowLayout {
                    id: sholderRow
                    property real childSizeSholder: (controller.width * 0.75) / 7.5
                    height: 120
                    Layout.rightMargin: 60
                    Layout.leftMargin: 60
                    spacing: 0
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    SholderButtons {
                        id: leftSholderButtons
                        width: 75
                        topButton.buttonText.text: "L2"
                        bottomButton.buttonText.text: "L1"
                        Layout.preferredHeight: 60
                        Layout.preferredWidth: sholderRow.childSizeSholder
                        Layout.fillHeight: true
                        Layout.maximumHeight: width
                    }
                    Rectangle {
                        visible: true
                        Layout.preferredHeight: leftSholderButtons.height
                        Layout.maximumHeight: leftSholderButtons.height
                        Layout.fillWidth: true
                        color: "transparent"
                    }

                    SholderButtons {
                        id: rightSholderButtons
                        width: 75
                        Layout.preferredHeight: 60
                        Layout.preferredWidth: sholderRow.childSizeSholder
                        topButton.buttonText.text: "R2"
                        bottomButton.buttonText.text: "R1"
                        Layout.fillHeight: true
                        Layout.maximumHeight: width
                    }
                }

                RowLayout {
                    id: buttonRow
                    spacing: 20
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    ContorllerDpadButtons {
                        id: dpadButtons
                        Layout.fillWidth: true
                        Layout.maximumHeight: width
                        Layout.preferredHeight: width
                        Layout.fillHeight: true
                    }

                    ContollerCenterButtons {
                        id: centerButtons
                        Layout.fillWidth: true
                        Layout.maximumHeight: width
                        Layout.preferredHeight: width
                        Layout.fillHeight: true
                    }

                    ControllerFourButtons {
                        id: faceButtons
                        Layout.fillWidth: true
                        Layout.maximumHeight: width
                        Layout.preferredHeight: width
                        Layout.fillHeight: true
                    }
                }

                RowLayout {
                    id: axisButtons
                    property real childSizeAxis: (controller.width * 0.75) / 6
                    Layout.maximumHeight: (controller.height / 3) * 0.30
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Rectangle {
                        visible: true
                        Layout.fillWidth: true

                        color: "transparent"
                    }
                    ControllerButton {
                        id: l3
                        buttonText.text: "L3"
                        Layout.maximumHeight: width
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: axisButtons.childSizeAxis
                        Layout.fillHeight: true
                    }
                    Rectangle {
                        visible: true
                        Layout.preferredHeight: 40
                        Layout.fillWidth: true
                        color: "transparent"
                    }
                    ControllerButton {
                        id: r3
                        buttonText.text: "R3"
                        Layout.maximumHeight: width
                        Layout.preferredWidth: axisButtons.childSizeAxis
                        Layout.preferredHeight: 40
                        Layout.fillHeight: true
                    }
                    Rectangle {
                        visible: true
                        Layout.preferredHeight: 40
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        color: "transparent"
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

