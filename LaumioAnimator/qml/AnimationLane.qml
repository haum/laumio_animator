import QtQuick 2.0

Item {
    id: lane
    property int laumio
    property bool selected
    signal clicked(var mouse)

    MouseArea {
        anchors.fill: parent
        onClicked: {
            lane.clicked(mouse)
        }
        Rectangle {
            anchors.fill: parent
            border.width: 1
            border.color: "#e0e0e0"
            color: "#4b4b4b"
            visible: true
        }
    }
}
