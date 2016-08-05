import QtQuick 2.0


Item {
    property var laumio
    property bool selected
    signal clicked()

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked()

        Rectangle {
            anchors.fill: parent
            color: "#5b5b5b"
            visible: selected
        }
    }

    Item {
        anchors {
            right: parent.right
            rightMargin: 10
            verticalCenter: parent.verticalCenter
        }
        height: parent.height
        width: height
        Rectangle {
            anchors.centerIn: parent
            height: (laumio && laumio.ip ? parent.height : parent.height / 2) - 5
            width: height
            color: laumio ? laumio.color : "#000"
            radius: width/2
        }
    }

    Column {
        anchors {
            left: parent.left
            leftMargin: 10
            verticalCenter: parent.verticalCenter
        }

        Text {
            text: laumio ? laumio.name : "<i>Laumio</i>"
            font.bold: true
            color: "#ffffff"
            font.pointSize: 10
        }

        Text {
            text: laumio ? laumio.ip : ""
            color: "#e0e0e0"
            font.pointSize: 10
        }
    }
}
