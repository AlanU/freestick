import QtQuick 2.4
import QtQuick.Controls 2.5

Item {
    width: 400
    height: 400

    Page {
        id: page
        anchors.fill: parent

        SwipeView {
            id: swipeView
            anchors.fill: parent
            currentIndex: tabBar.currentIndex
            JoystickTablePage {
                width: swipeView.width
                height: swipeView.height
            }

            Pane {
                width: swipeView.width
                height: swipeView.height

                Column {
                    spacing: 40
                    width: parent.width

                    Label {
                        width: parent.width
                        wrapMode: Label.Wrap
                        horizontalAlignment: Qt.AlignHCenter
                        text: "TabBar is a bar with icons or text which allows the user"
                              + "to switch between different subtasks, views, or modes."
                    }
                }
            }
            Pane {
                width: swipeView.width
                height: swipeView.height

                Column {
                    spacing: 40
                    width: parent.width

                    Label {
                        width: parent.width
                        wrapMode: Label.Wrap
                        horizontalAlignment: Qt.AlignHCenter
                        text: "TabBar is a bar with icons or text which allows the user"
                              + "to switch between different subtasks, views, or modes."
                    }
                }
            }
        }

        footer: TabBar {
            id: tabBar
            currentIndex: swipeView.currentIndex

            TabButton {
                text: "First"
            }
            TabButton {
                text: "Second"
            }
            TabButton {
                text: "Third"
            }
        }
    }
}
