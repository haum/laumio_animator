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

    contentItem: Rectangle {
        color: "#3b3b3b"
        implicitWidth: 360
        implicitHeight: 260
        Text{
            text: "First Lower Color"
            anchors.top: parent.top
            anchors.left: animFirstLowerColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: animFirstLowerColor
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 20
            anchors.topMargin: 20
            text: animation.firstLowerColor
            width: 150
        }
        Text{
            text: "Last Lower Color"
            anchors.top: parent.top
            anchors.left: animLastLowerColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: animLastLowerColor
            anchors.left: animFirstLowerColor.right
            anchors.top: parent.top
            anchors.leftMargin: 20
            anchors.topMargin: 20
            text: animation.lastLowerColor
            width: 150
        }

        Text{
            text: "First Upper Color"
            anchors.top: animLastLowerColor.bottom
            anchors.left: animFirstUpperColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: animFirstUpperColor
            anchors.top: animFirstLowerColor.bottom
            anchors.left: animFirstLowerColor.left
            anchors.topMargin: 20
            text: animation.firstUpperColor
            width: 150
        }
        Text{
            text: "Last Upper Color"
            anchors.top: animLastLowerColor.bottom
            anchors.left: animLastUpperColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: animLastUpperColor
            anchors.top: animLastLowerColor.bottom
            anchors.left: animLastLowerColor.left
            anchors.topMargin: 20
            text: animation.lastUpperColor
            width: 150
        }

        Text{
            text: "Beginning"
            anchors.top: animFirstUpperColor.bottom
            anchors.left: animFirstUpperColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: beginning
            anchors.top: animFirstUpperColor.bottom
            anchors.left: animFirstUpperColor.left
            anchors.topMargin: 20
            text: animation.fromStart
            width: 150
        }
        Text{
            text: "Duration"
            anchors.top: animLastUpperColor.bottom
            anchors.left: duration.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: duration
            anchors.top: animLastUpperColor.bottom
            anchors.left: animLastUpperColor.left
            anchors.topMargin: 20
            text: animation.duration
            width: 150
        }

        Text{
            text: "Frequency"
            anchors.top: beginning.bottom
            anchors.left: frequency.left
            anchors.topMargin: 5            
            color: "#fff"
        }
        TextField{
            id: frequency
            anchors.top: beginning.bottom
            anchors.left: animFirstUpperColor.left
            anchors.topMargin: 20
            text: animation.pulsation / (2 * Math.PI)
            width: 150
        }
        Text{
            text: "Delay"
            anchors.top: duration.bottom
            anchors.left: delay.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: delay
            anchors.top: duration.bottom
            anchors.left: duration.left
            anchors.topMargin: 20
            text: animation.delay
            width: 150
        }

        LAButton {
            text: "Save bounded pulsing color animation"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            height: 40
            onClicked: {
                animation.firstLowerColor = animFirstLowerColor.text
                animation.lastLowerColor = animLastLowerColor.text
                animation.firstUpperColor = animFirstUpperColor.text
                animation.lastUpperColor = animLastUpperColor.text
                animation.fromStart = parseFloat(beginning.text)
                animation.duration = parseFloat(duration.text)
                animation.pulsation = parseFloat(frequency.text) * 2 * Math.PI
                animation.delay = parseFloat(delay.text)
                boundedPulsingColorPopup.close()
            }
        }
    }


}
