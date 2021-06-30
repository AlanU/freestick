import QtQuick 2.4
import QtQuick.Layouts 1.12

GridLayout {
    id: root
    width: 100
    height: 100
    property alias stick: stick
    property alias axis: axis
    Rectangle {
        id: axis
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: "white"
        Rectangle {
            width: 2
            height: parent.height
            color: "black"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Rectangle {
            width: parent.width
            height: 2
            color: "black"
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            id: stick
            implicitHeight: axis.height * 0.20
            implicitWidth: axis.width * 0.20
            //Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            color: "transparent"
            property color buttonColor: "red"
            Rectangle {
                width: 2
                height: parent.height
                color: parent.buttonColor
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Rectangle {
                width: parent.width
                height: 2
                color: parent.buttonColor
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
