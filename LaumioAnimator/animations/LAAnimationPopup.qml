import QtQuick 2.7
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
        implicitHeight: 120
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
        LAButton {
            text: "Create animation"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            height: 40
            onClicked: {
                console.log(Qt.resolvedUrl("LA" + animChoice.currentText + ".qml"))
                var component = Qt.createComponent(Qt.resolvedUrl("LA" + animChoice.currentText + ".qml"))
                if (component.status === Component.Ready) {
                    var dialog = component.createObject(parent, {laumioIdx: laumioIndex})
                } else console.log(component.errorString())
                animationPopup.close()
            }
        }
    }
}
