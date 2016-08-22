import QtQuick 2.0

RPanel {
    id: panel
    followList: false

    Repeater {
        model: anim
        delegate: Item {
            id: draggable
            property var laumio: model.laumio
            x: laumio.x * panel.width - width/2
            y: laumio.y * panel.height - height/2
            height: 40
            width: height
            Rectangle {
                anchors.centerIn: parent
                height: (laumio && laumio.ip ? parent.height : parent.height / 2) - 5
                width: height
                color: laumio ? laumio.color : "#000"
                radius: width/2
                MouseArea {
                    anchors.fill: parent
                    drag.target: draggable
                }
            }
            onXChanged: laumio.x = (x + width/2) / panel.width
            onYChanged: laumio.y = (y + height/2) / panel.height
        }
    }
}
