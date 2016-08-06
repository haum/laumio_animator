import QtQuick 2.0
import QtQuick.Dialogs 1.0
import Laumio 1.0
import "widgets"

Item {
    LaumioAnimation {
        id: anim
    }
    Rectangle {
        id: header
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: 70
        color: "#3b3b3b"
        FileDialog {
            id: fileDialog
            property var cb
            title: "Please choose a file"
            onAccepted: if (cb != undefined) cb(fileUrl)
        }
        Row {
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                right: parent.right
                leftMargin: 10
                rightMargin: 10
            }
            spacing: 10
            LAButton {
                text: "Open"
                onClicked: {
                    fileDialog.selectExisting = true;
                    fileDialog.cb = function (file) {
                        anim.loadFromFile(file);
                    };
                    fileDialog.visible = true;
                }
            }
            LAButton {
                text: "Save"
                onClicked: {
                    fileDialog.selectExisting = false;
                    fileDialog.cb = function (file) {
                        anim.saveToFile(file);
                    };
                    fileDialog.visible = true;
                }
            }
            LAButton {
                text: "Timeline"
                onClicked: rightZoneLoader.source = "TimeLineRPanel.qml"
            }
            LAButton {
                text: "Preview"
                onClicked: rightZoneLoader.source = "PreviewRPanel.qml"
            }
        }
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
        Rectangle {
            color: "#3b3b3b"
            width: 1
            height: parent.height
            anchors.left: parent.left
        }
    }
    Flickable {
        anchors {
            top: header.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        contentHeight: Math.max(listColumn.height, bgLeft.height)
        clip: true

        Column {
            id: listColumn
            property var selected: undefined
            anchors {
                top: parent.top
                topMargin: 10
            }
            width: 150
            Repeater {
                model: anim
                delegate: LaumioMenu {
                    width: parent.width
                    height: 50
                    laumio: model.laumio
                    selected: listColumn.selected == this
                    onClicked: {
                        if (listColumn.selected == this)
                            listColumn.selected = undefined;
                        else
                            listColumn.selected = this;
                    }
                    onRemoveMe: anim.deleteLaumio(index)
                }
            }
            LAButton {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "New Laumio"
                onClicked: anim.newLaumio()
            }
        }
        Loader {
            id: rightZoneLoader
            property var selectedLaumio: listColumn.selected ? listColumn.selected.laumio : undefined
            property var anim: anim
            clip: true
            anchors {
                top: parent.top
                topMargin: 10
                bottom: item && item.followList ? listColumn.bottom : parent.bottom
                left: listColumn.right
                leftMargin: 10
                right: parent.right
            }
        }
    }
}
