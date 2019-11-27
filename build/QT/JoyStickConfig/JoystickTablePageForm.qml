//import QtQuick.Controls 1.4 as OldControls
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
Item {
    id:root
    width: 400
    height: 400
    property alias model: tableView.model
    property alias deviceModel: devices.model
    property alias devicesControl: devices
    property alias tableView: tableView
    property var columnNames: ["ID", "Min Value", "Max Value","Raw Value", "Value", "Dead Min","Dead Max","Mapped","Element Cookie","Usage Page","Usage"]
    Page {
        id: page
        anchors.fill: parent
        header:  ComboBox{
            id: devices
        }
        TableView {
            id: tableView
            anchors.fill: parent
            columnWidthProvider: function (column) { return 100; }
            topMargin: 20
            delegate: Rectangle {
                implicitWidth: 100
                implicitHeight: 50
                Text {
                    text: display
                }
            }

            Row{
                id:headers
                y:tableView.contentY
                z:2
                Repeater{
                    model: tableView.columns > 0 ? tableView.columns : 1
                    Label{
                        width: tableView.columnWidthProvider(modelData)
                        height: 20
                        text: root.columnNames[modelData]
                        color: '#aaaaaa'
                        background: Rectangle { color: "#333333" }
                    }
                }
            }

            /*OldControls.TableViewColumn {
                role: "ID"
                title: "ID"
                width: 100
            }
            OldControls.TableViewColumn {
                role: "Min Value Range"
                title: "Min Value Range"
                width: 200
            }
            OldControls.TableViewColumn {
                role: "Max Value Range"
                title: "Max Value Range"
                width: 200
            }
            OldControls.TableViewColumn {
                role: "Raw Value"
                title: "Raw Value"
                width: 100
            }
            OldControls.TableViewColumn {
                role: "Value"
                title: "Value"
                width: 100
            }
            OldControls.TableViewColumn {
                role: "Dead Min"
                title: "Dead Min"
                width: 200
            }
            OldControls.TableViewColumn {
                role: "Dead Max"
                title: "Dead Max"
                width: 200
            }
            OldControls.TableViewColumn {
                role: "Mapped"
                title: "Mapped"
                width: 100
            }
            OldControls.TableViewColumn {
                role: "Element Cookie"
                title: "Element Cookie"
                width: 200
            }
            OldControls.TableViewColumn {
                role: "Usage Page"
                title: "Usage Page"
                width: 200
            }
            OldControls.TableViewColumn {
                role: "Usage"
                title: "Usage"
                width: 100
            }*/
        }
    }
}
