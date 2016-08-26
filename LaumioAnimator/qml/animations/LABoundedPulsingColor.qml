import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import "../widgets"

Dialog {
    id: boundedPulsingColorPopup
    property var animation
    visible: true
    title: "Bounded Pulsing Color Animation"
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
                text: "First Lower Color"
                color: "#fff"
            }
            TextField{
                id: animFirstLowerColor
                text: animation.firstLowerColor
                width: parent.width
            }
            Text{
                text: "Last Lower Color"
                color: "#fff"
            }
            TextField{
                id: animLastLowerColor
                text: animation.lastLowerColor
                width: parent.width
            }

            Text{
                text: "First Upper Color"
                color: "#fff"
            }
            TextField{
                id: animFirstUpperColor
                text: animation.firstUpperColor
                width: parent.width
            }
            Text{
                text: "Last Upper Color"
                color: "#fff"
            }
            TextField{
                id: animLastUpperColor
                text: animation.lastUpperColor
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
                text: "Save bounded pulsing color animation"
                height: 40
                onClicked: {
                    if (parseFloat(duration.text) !== 0)
                    {
                        animation.firstLowerColor = animFirstLowerColor.text
                        animation.lastLowerColor = animLastLowerColor.text
                        animation.firstUpperColor = animFirstUpperColor.text
                        animation.lastUpperColor = animLastUpperColor.text
                        animation.fromStart = parseFloat(beginning.text)
                        animation.duration = parseFloat(duration.text)
                        animation.pulsation = parseFloat(frequency.text) * 2 * Math.PI
                        animation.delay = parseFloat(delay.text)
                        animation.priority = parseInt(priority.text)
                        boundedPulsingColorPopup.close()
                    }
                }
            }
        }
    }
}
