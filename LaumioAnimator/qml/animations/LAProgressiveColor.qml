import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import "../widgets"

Dialog {
    id: progressiveColorPopup
    property var animation
    visible: true
    title: "Progressive Color Animation"
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
                text: "First Color"
                color: "#fff"
            }
            TextField{
                id: animFirstColor
                text: animation.firstColor
                width: parent.width
            }
            Text{
                text: "Last Color"
                color: "#fff"
            }
            TextField{
                id: animLastColor
                text: animation.lastColor
                width: parent.width
            }

            Text{
                text: "Beginning"
                color: "#fff"
            }
            TextField{
                id: beginning
                text: animation.fromStart
                width: parent.width
            }
            Text{
                text: "Duration"
                color: "#fff"
            }
            TextField{
                id: duration
                text: animation.duration
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
                text: "Save progressive color animation"
                onClicked: {
                    animation.firstColor = animFirstColor.text
                    animation.lastColor = animLastColor.text
                    animation.fromStart = parseFloat(beginning.text)
                    animation.duration = parseFloat(duration.text)
                    animation.priority = parseInt(priority.text)
                    progressiveColorPopup.close()
                }
            }
        }
    }
}
