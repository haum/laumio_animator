import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Button {
    Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor
    style: ButtonStyle {
        background: Rectangle {
            implicitHeight: 24
            implicitWidth: 100
            color: control.hovered ? "#6c6c6c" : "#5c5c5c"
            border.color: "#3c3c3c"
            border.width: 1
            radius: 3
        }
        label: Label {
            color: "white"
            text: control.text
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}

