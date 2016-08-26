import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import "../widgets"

Dialog {
    id: pulsingColorPopup
    property var animation
    visible: true
    title: "Pulsing Color Animation"
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
                text: "Mean Color"
                color: "#fff"
            }
            TextField{
                id: animMeanColor
                text: animation.meanColor
                width: parent.width
            }
            Text{
                text: "Color Variation"
                color: "#fff"
            }
            TextField{
                id: animVarColor
                text: animation.varColor
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
                text: "Frequency"
                color: "#fff"
            }
            TextField{
                id: frequency
                text: animation.pulsation / (2 * Math.PI)
                width: parent.width
            }
            Text{
                text: "Delay"
                color: "#fff"
            }
            TextField{
                id: delay
                text: animation.delay
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
                text: "Save pulsing color animation"
                onClicked: {
                    animation.meanColor = animMeanColor.text
                    animation.varColor = animVarColor.text
                    animation.fromStart = parseFloat(beginning.text)
                    animation.duration = parseFloat(duration.text)
                    animation.pulsation = parseFloat(frequency.text) * 2 * Math.PI
                    animation.delay = parseFloat(delay.text)
                    animation.priority = parseInt(priority.text)
                    pulsingColorPopup.close()
                }
            }

        }
    }


}
