import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import "../widgets"

Dialog {
    id: progressiveColorPopup
    property int laumioIdx
    visible: true
    title: "Progressive Color Animation"
    modality: Qt.WindowModal

    contentItem: Rectangle {
        color: "#3b3b3b"
        implicitWidth: 360
        implicitHeight: 180
        Text{
            text: "First Color"
            anchors.top: parent.top
            anchors.left: animFirstColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: animFirstColor
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 20
            anchors.topMargin: 20
            width: 150
        }
        Text{
            text: "Last Color"
            anchors.top: parent.top
            anchors.left: animLastColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: animLastColor
            anchors.left: animFirstColor.right
            anchors.top: parent.top
            anchors.leftMargin: 20
            anchors.topMargin: 20
            width: 150
        }

        Text{
            text: "Beginning"
            anchors.top: animFirstColor.bottom
            anchors.left: animFirstColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: beginning
            anchors.top: animFirstColor.bottom
            anchors.left: animFirstColor.left
            anchors.topMargin: 20
            width: 150
        }
        Text{
            text: "Duration"
            anchors.top: animLastColor.bottom
            anchors.left: duration.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: duration
            anchors.top: animLastColor.bottom
            anchors.left: animLastColor.left
            anchors.topMargin: 20
            width: 150
        }
        LAButton {
            text: "Create progressive color animation"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            height: 40
            onClicked: {
                var animation = anim.newAnimation(laumioIdx, "ProgressiveColor")
                animation.firstColor = animFirstColor.text
                animation.lastColor = animLastColor.text
                animation.fromStart = parseFloat(beginning.text)
                animation.duration = parseFloat(duration.text)
                progressiveColorPopup.close()
            }
        }
    }


}
