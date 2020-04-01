import QtQuick 2.4
import QtQuick.Controls 2.5

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
        header: ComboBox {
            id: devices
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

        footer: TabBar {
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
    }
}