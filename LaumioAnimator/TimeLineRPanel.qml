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
                    laumio: index
                    property var laneModel: model
                    width: parent.width - 10
                    height: 50
                    Repeater {
                        id: animationRepeater
                        property int laumioNb: index
                        model: laneModel.animations
                        delegate: Rectangle{
                            MouseArea {
                                anchors.fill: parent
                                drag.target: parent
                                drag.minimumX: 0
                                drag.axis: Drag.XAxis
                                drag.onActiveChanged: {
                                    if (drag.active == false) {
                                        modelData.fromStart = parent.x / timeExpand
                                    }
                                }
                            }

                            property real timeExpand: 100
                            x: modelData.fromStart * timeExpand
                            width: modelData.duration * timeExpand
                            height: parent.height
                            border.width: 1
                            border.color: "#e0e0e0"
                            color: "#ff0000"
                            opacity: 0.8
                            visible: true
                            Text{
                                text: laneModel.laumio.name + "<br>" + modelData.name
                            }
                        }
                    }
                }
            }
        }
    }

}
