import QtQuick 2.0
import "widgets"

Item {
    property int laumio
    property bool selected
    signal clicked()

    MouseArea {
        anchors.fill: parent
        onClicked: {
            var component = Qt.createComponent("animations/LAAnimationPopup.qml")
            if (component.status === Component.Ready) {
                var dialog = component.createObject(parent,{laumioIndex: laumio});
            }
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
