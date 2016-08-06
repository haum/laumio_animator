import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

TextField {
    style: TextFieldStyle {
        textColor: "white"
        placeholderTextColor: "#6c6c6c"
        background: Rectangle {
            radius: 3
            implicitWidth: 100
            implicitHeight: 24
            border.color: control.activeFocus ? "#6c6c6c" : "#5c5c5c"
            border.width: 1
            color: control.activeFocus ? "#3c3c3c" : "#4c4c4c"
        }
    }
}
