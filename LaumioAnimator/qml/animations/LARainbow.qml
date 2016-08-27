import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import "../widgets"

Dialog {
    id: rainbowPopup
    property var animation
    visible: true
    title: "Rainbow Animation"
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
                text: "Save rainbow animation"
                onClicked: {
                    animation.fromStart = parseFloat(beginning.text)
                    animation.duration = parseFloat(duration.text)
                    animation.priority = parseInt(priority.text)
                    rainbowPopup.close()
                }
            }
        }
    }


}
