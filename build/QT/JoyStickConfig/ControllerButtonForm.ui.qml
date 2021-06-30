import QtQuick 2.4

Item {
    id: item1
    width: 100
    height: 100
    property alias button: button
    property alias buttonText: buttonText
    property bool rounded: true
    antialiasing: true

    Rectangle {
        id: button
        color: "#ffffff"
        width: rounded ? parent.width < parent.height ? parent.width : parent.height : parent.width
        border.color: "black"
        border.width: 1
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        radius: width * 0.5
        height: rounded ? width : parent.height

        Text {
            id: buttonText
            y: 43
            text: qsTr("Text")
            horizontalAlignment: Text.AlignHCenter
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
        }
    }
}
