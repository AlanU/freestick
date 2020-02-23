import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: element2
    width: 400
    height: 400
    property alias frendlyname: frendlyname
    property alias productID: productID
    property alias vendorID: venderID
    property alias productName: productName
    property alias vendorName: venderName
    Page {
        anchors.fill: parent
        Text {
            id: frendlyname
            text: qsTr("Conroller Friendly name")
            horizontalAlignment: Text.AlignHCenter
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 356
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
        }

        Grid {
            id: grid
            columns: 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.right: parent.right
            anchors.rightMargin: 50
            spacing: 19

            Text {
                id: venderNameLabel
                text: qsTr("Vendor Name")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
                width: parent.width / 2
            }

            Text {
                id: venderName
                text: qsTr("Text")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
                width: parent.width / 2
            }
            Text {
                id: productNameLabel
                text: qsTr("Product Name")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
                width: parent.width / 2
            }

            Text {
                id: productName
                text: qsTr("Text")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
                width: parent.width / 2
            }
            Text {
                id: venderIDLabel
                text: qsTr("Vendor ID")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
                width: parent.width / 2
            }

            Text {
                id: venderID
                text: qsTr("Text")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
                width: parent.width / 2
            }
            Text {
                id: productIDLabel
                text: qsTr("product ID")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
                width: parent.width / 2
            }

            Text {
                id: productID
                text: qsTr("Text")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
                width: parent.width / 2
            }
        }
    }
}
