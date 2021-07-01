import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Item {
    id: mainForm
    width: 400
    height: 400
    property alias swipeView: swipeView
    property alias tabBar: tabBar
    property alias deviceModel: devices.model
    property alias devicesControl: devices
    property int currentControllerID: 0
    Page {
        id: page
        anchors.fill: parent
        header: ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            TabBar {
                Layout.fillWidth: true
                id: tabBar
                TabButton {
                    text: "Infomation"
                }
                TabButton {
                    text: "Controller"
                }
                TabButton {
                    text: "Input Table"
                }
            }
            ComboBox {
                id: devices
                Layout.fillWidth: true
            }
        }

        SwipeView {
            id: swipeView
            anchors.fill: parent
            interactive: false
            JoystickInformationPage {
                id: contorllerInfoPage
                width: swipeView.width
                height: swipeView.height
                currentInfoPageControllerID: mainForm.currentControllerID
            }

            JoystickDiagram {
                id: diagramPage
                width: swipeView.width
                height: swipeView.height
                currentInfoPageControllerID: mainForm.currentControllerID
            }

            JoystickTablePage {
                id: contorllerTable
                width: swipeView.width
                height: swipeView.height
                currentTableContorllerID: mainForm.currentControllerID
            }
        }

        //for mobile

        /*footer: TabBar {
            id: tabBar
            TabButton {
                text: "Infomation"
            }
            TabButton {
                text: "Controller"
            }
            TabButton {
                text: "Input Table"
            }
        }*/
    }
}
