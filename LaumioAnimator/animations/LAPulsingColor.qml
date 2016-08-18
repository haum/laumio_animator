import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import "../widgets"

Dialog {
    id: pulsingColorPopup
    property int laumioIdx
    visible: true
    title: "Pulsing Color Animation"
    modality: Qt.WindowModal

    contentItem: Rectangle {
        color: "#3b3b3b"
        implicitWidth: 360
        implicitHeight: 220
        Text{
            text: "Mean Color"
            anchors.top: parent.top
            anchors.left: animMeanColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: animMeanColor
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 20
            anchors.topMargin: 20
            width: 150
        }
        Text{
            text: "Color Variation"
            anchors.top: parent.top
            anchors.left: animVarColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: animVarColor
            anchors.left: animMeanColor.right
            anchors.top: parent.top
            anchors.leftMargin: 20
            anchors.topMargin: 20
            width: 150
        }

        Text{
            text: "Beginning"
            anchors.top: animMeanColor.bottom
            anchors.left: animMeanColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: beginning
            anchors.top: animMeanColor.bottom
            anchors.left: animMeanColor.left
            anchors.topMargin: 20
            width: 150
        }
        Text{
            text: "Duration"
            anchors.top: animVarColor.bottom
            anchors.left: duration.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: duration
            anchors.top: animVarColor.bottom
            anchors.left: animVarColor.left
            anchors.topMargin: 20
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
            anchors.left: animMeanColor.left
            anchors.topMargin: 20
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
            width: 150
        }

        LAButton {
            text: "Create pulsing color animation"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            height: 40
            onClicked: {
                var animation = anim.newAnimation(laumioIdx, "PulsingColor")
                animation.meanColor = animMeanColor.text
                animation.varColor = animVarColor.text
                animation.fromStart = parseFloat(beginning.text)
                animation.duration = parseFloat(duration.text)
                animation.frequency = parseFloat(frequency.text)
                animation.delay = parseFloat(delay.text)
                pulsingColorPopup.close()
            }
        }
    }


}
