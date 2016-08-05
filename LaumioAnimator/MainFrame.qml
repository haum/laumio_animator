import QtQuick 2.0

Item {
    Rectangle {
        id: header
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: 70
        color: "#3b3b3b"
    }
    Rectangle {
        id: bgLeft
        anchors {
            top: header.bottom
            bottom: parent.bottom
            left: parent.left
        }
        width: 150
        color: "#4b4b4b"
    }
    Rectangle {
        anchors {
            top: header.bottom
            bottom: parent.bottom
            left: bgLeft.right
            right: parent.right
        }
        color: "#5b5b5b"
    }
    Rectangle {
        color: "#3b3b3b"
        width: 1
        height: parent.height
        anchors.left: bgLeft.right
    }
    Flickable {
        anchors {
            top: header.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        contentHeight: listColumn.height
        clip:true

        Column {
            id: listColumn
            property int selected: -1
            anchors {
                top: parent.top
                topMargin: 10
            }
            width: 150
            Repeater {
                model: 5
                delegate: LaumioMenu {
                    width: parent.width
                    height: 50
                    selected: listColumn.selected == index
                    onClicked: {
                        if (listColumn.selected == index)
                            listColumn.selected = -1;
                        else
                            listColumn.selected = index;
                    }
                }
            }
        }
        Loader {
            anchors {
                top: parent.top
                topMargin: 10
                bottom: listColumn.bottom
                left: listColumn.right
                leftMargin: 10
                right: parent.right
            }
            source: "TimeLine.qml"
        }
    }
}
