import QtQuick 2.4

Item {
    id: root
    height: rounded === true ? 100 : 50
    property alias button: button
    property alias buttonText: buttonText
    property alias buttonBorder: button.border.width
    property bool rounded: false
    width: 60
    antialiasing: true

    Rectangle {
        id: button
        color: "#ffffff"
        width: buttonText.childrenRect.width
        //width: rounded ? parent.width < parent.height ? parent.width : parent.height : parent.width
        border.color: "black"
        border.width: 0
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        radius: width * 0.5
        height: rounded ? width : parent.height / 2
    }
    Text {
        id: buttonText
        text: qsTr("Text")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: parent.horizontalCenter
        minimumPointSize: 9
        minimumPixelSize: 9
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        fontSizeMode: Text.VerticalFit
        anchors.top: root.rounded ? parent.top : button.bottom
        anchors.bottom: parent.bottom
    }
}
