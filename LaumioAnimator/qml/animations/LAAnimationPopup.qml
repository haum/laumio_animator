import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import "../widgets"

Dialog {
    id: animationPopup
    property int laumioIndex
    visible: true
    title: "Animation"
    modality: Qt.WindowModal

    contentItem: Rectangle {
        color: "#3b3b3b"
        implicitWidth: 360
        implicitHeight: 240
        Text {
            text: "Animation type"
            anchors.top: parent.top
            anchors.left: animChoice.left
            anchors.topMargin: 5
            color: "#fff"
        }
        ComboBox {
            id: animChoice
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 25
            width: 340
            model: anim.factoriesNames()
        }
        Text{
            id: priorityText
            text: "Priority"
            anchors.left: animChoice.left
            anchors.top: animChoice.bottom
            anchors.topMargin: 10
            color: "#fff"
        }
        TextField{
            id: animPriority
            anchors{
                top: priorityText.bottom
                topMargin: 10
                left: animChoice.left
            }
            width: 340
            text:"0"
        }
        LAButton {
            text: "Create animation"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            height: 40
            onClicked: {
                var animation = anim.newAnimation(laumioIndex, animChoice.currentText)
                animation.priority = parseInt(animPriority.text)
                var component = Qt.createComponent(Qt.resolvedUrl("LA" + animChoice.currentText + ".qml"))
                if (component.status === Component.Ready) {
                    var dialog = component.createObject(parent, {animation: animation})
                } else console.log(component.errorString())
                animationPopup.close()
            }
        }
    }
}
