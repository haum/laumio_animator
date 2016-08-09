import QtQuick 2.0

RPanel {
    Flickable {
        anchors.fill: parent
        Column {
            id: nameColumn
            property var selected: undefined
            anchors {
                top: parent.top
            }
            width: parent.width
            Repeater {
                id: laumioRepeater
                model: anim
                delegate: AnimationLane {
                    property var laneModel: model
                    width: parent.width - 10
                    height: 50
                    Row {
                        Repeater {
                            id: animationRepeater
                            property int laumioNb: index
                            model: laneModel.animations
                            delegate: Rectangle{
                                width: 150
                                height: parent.height
                                border.width: 1
                                border.color: "#e0e0e0"
                                color: "#ff0000"
                                visible: true
                                Text{
                                    text: laneModel.index + " " + index
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}
