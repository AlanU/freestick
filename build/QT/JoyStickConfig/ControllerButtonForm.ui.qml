import QtQuick 2.4

Item {
    width: 100
    height: 100
    property alias button: button
    property alias buttonText: buttonText
    antialiasing: true

    Rectangle {
        id: button
        color: "#ffffff"
        width: parent.width < parent.height ? parent.width : parent.height
        border.color: "black"
        border.width: 1
        radius: width * 0.5
        height: width

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
