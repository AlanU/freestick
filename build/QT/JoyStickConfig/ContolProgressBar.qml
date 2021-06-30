import QtQuick 2.0
Rectangle {
    id:rootRect
    width:400
    height:100

    property real min: 0
    property real value:0
    property real max: 0
    property real boarderThikness: 0.5
    property real xOffset: 0.1
    property real yOffset: 0.1
    property alias forgroundColor: forgroundRect.color
    property alias borderColor: rootRect.border.color

    border.width: rootRect.boarderThikness * rootRect.height
    radius:rootRect.boarderThikness * height

    Rectangle{
        id:forgroundRect
        x: xOffset * rootRect.height
        y: yOffset * rootRect.height
        width: Math.max(height,
               Math.min((value - min) / (max - min) * (parent.width - 0.2 * rootRect.height),
                        parent.width - 0.2 * rootRect.height))
        height: 0.8 * rootRect.height
        color:"green"
        radius: parent.radius
        visible: rootRect.value > rootRect.min
    }
}
