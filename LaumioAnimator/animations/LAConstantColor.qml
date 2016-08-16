import QtQuick 2.7
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import "../widgets"

Dialog {
    id: constantColorPopup
    property int laumioIdx
    visible: true
    title: "Constant Color Animation"
    modality: Qt.WindowModal

    contentItem: Rectangle {
        color: "#3b3b3b"
        implicitWidth: 360
        implicitHeight: 180
        Text{
            text: "Color"
            anchors.top: parent.top
            anchors.left: animColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: animColor
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20
            width: 340
        }
        Text{
            text: "Beginning"
            anchors.top: animColor.bottom
            anchors.left: animColor.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: beginning
            anchors.top: animColor.bottom
            anchors.left: animColor.left
            anchors.topMargin: 20
            width: 160
        }
        Text{
            text: "Duration"
            anchors.top: animColor.bottom
            anchors.left: duration.left
            anchors.topMargin: 5
            color: "#fff"
        }
        TextField{
            id: duration
            anchors.top: animColor.bottom
            anchors.right: animColor.right
            anchors.topMargin: 20
            width: 160
        }
        LAButton {
            text: "Create constant color animation"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            height: 40
            onClicked: {
                var animation = anim.newAnimation(laumioIdx, "ConstantColor")
                animation.color = animColor.text
                animation.fromStart = parseFloat(beginning.text)
                animation.duration = parseFloat(duration.text)
                constantColorPopup.close()
            }
        }
    }


}
