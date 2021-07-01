import QtQuick 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15

Item {
    id: root
    width: 400
    height: 50
    property bool precent: true
    property alias value: progressBar.value
    property alias elemnetName: elementLabel.text
    property alias min: progressBar.min
    property alias max: progressBar.max
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        Label {
            id: elementLabel
            text: qsTr("Label")
            Layout.fillWidth: true
        }

        ContolProgressBar {
            id: progressBar
            min: 0
            value: 50
            max: 100
            borderColor: "#EEEEEE"
            forgroundColor: "#49E746"
            Layout.fillWidth: true
            Layout.fillHeight: true
            property real offsetValue: progressBar.min < 0 ? 0 - progressBar.min : 0
            Label {
                anchors.centerIn: parent
                text: root.precent === true ? Math.floor(
                                                  ((parent.value + parent.offsetValue)
                                                   / (parent.max + parent.offsetValue))
                                                  * 100) + "%" : parent.value
            }
        }
    }
}
