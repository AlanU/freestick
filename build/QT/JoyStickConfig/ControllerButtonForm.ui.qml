import QtQuick 2.4

Item {
    id: item1
    width: 100
    height: 100
    property alias button: button
    property alias buttonText: buttonText
    property alias buttonBorder: button.border.width
    property bool rounded: true
    antialiasing: true

    Rectangle {
        id: button
        color: "#ffffff"
        width: rounded ? parent.width < parent.height ? parent.width : parent.height : parent.width
        border.color: "black"
        border.width: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        radius: width * 0.5
        height: rounded ? width : parent.height

        Text {
            id: buttonText
            text: qsTr("Text")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            minimumPointSize: 9
            minimumPixelSize: 9
            anchors.bottomMargin: 20
            anchors.topMargin: 20
            fontSizeMode: Text.VerticalFit
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 10
        }
    }
}
