import QtQuick 2.0

Item {
    property var laumio
    property bool selected
    signal clicked()

    MouseArea {
        anchors.fill: parent
        Rectangle {
            anchors.fill: parent
            border.width: 1
            border.color: "#e0e0e0"

            color: "#4b4b4b"
            visible: true
        }
    }
}
