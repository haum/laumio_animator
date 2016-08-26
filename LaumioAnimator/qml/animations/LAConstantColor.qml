import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import "../widgets"

Dialog {
    id: constantColorPopup
    property var animation
    visible: true
    title: "Constant Color Animation"
    modality: Qt.WindowModal
    width: col.width
    height: col.height

    contentItem: Rectangle {
        color: "#3b3b3b"
        implicitWidth: col.width
        implicitHeight: col.height
        Column {
            id: col
            Text{
                text: "Color"
                color: "#fff"
            }
            TextField{
                id: animColor
                text: animation.color
                width: parent.width
            }
            Text{
                text: "Beginning"
                color: "#fff"
            }
            TextField{
                id: beginning
                text: animation.fromStart.toString()
                width: parent.width
            }
            Text{
                text: "Duration"
                color: "#fff"
            }
            TextField{
                id: duration
                text: animation.duration.toString()
                width: parent.width
            }
            Text{
                text: "Priority"
                color: "#fff"
            }
            TextField{
                id: priority
                text: animation.priority.toString()
                width: parent.width
            }
            LAButton {
                text: "Save constant color animation"
                onClicked: {
                    animation.color = animColor.text
                    animation.fromStart = parseFloat(beginning.text)
                    animation.duration = parseFloat(duration.text)
                    animation.priority = parseInt(priority.text)
                    constantColorPopup.close()
                }
            }
        }
    }


}
