import QtQuick 2.5
import QtQuick.Controls 1.4
import Laumio 1.0
import "widgets"

RPanel {
    Text {
        anchors.centerIn: parent
        text: "Aucun Laumio sélectionné"
        color: "#9b9b9b"

        visible: selectedLaumio === undefined
    }

    Column {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.topMargin: 10

        spacing: 10
        visible: selectedLaumio !== undefined

        // General
        Column {
            spacing: 10
            width: parent.width

            LATitle {
                text: "Général"
            }

            Grid {
                columns: 2
                spacing: 5
                columnSpacing: 10
                horizontalItemAlignment: Grid.AlignRight
                verticalItemAlignment: Grid.AlignVCenter
                anchors.horizontalCenter: parent.horizontalCenter

                LALabel {
                    text: "Nom"
                }

                LATextField {
                    id: nameField
                    text: selectedLaumio ? selectedLaumio.name : ""
                    width: 160
                    onTextChanged: {
                        if (selectedLaumio && selectedLaumio.name !== text) {
                            selectedLaumio.name = text;
                        }
                    }
                }

                LALabel {
                    text: "Adresse IP"
                }

                LATextField {
                    id: ipField
                    text: selectedLaumio ? selectedLaumio.ip : "0.0.0.0"
                    width: 160
                    onTextChanged: {
                        if (selectedLaumio && selectedLaumio.ip !== text) {
                            selectedLaumio.ip = text;
                        }
                    }

                    validator: RegExpValidator { regExp: /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/ }
                }

                LALabel {
                    id: longText
                    text: "LED à piloter"
                }

                LATextField {
                    id: ledField
                    width: 160
                    placeholderText: "de 0 à 12, ou 255"
                }


                LALabel {
                    text: "X"
                }

                LATextField {
                    text: selectedLaumio ? selectedLaumio.x : ""
                    width: 160
                    onTextChanged: {
                        if (selectedLaumio && selectedLaumio.x !== text) {
                            selectedLaumio.x = text;
                        }
                    }
                }

                LALabel {
                    text: "Y"
                }

                LATextField {
                    text: selectedLaumio ? selectedLaumio.y : ""
                    width: 160
                    onTextChanged: {
                        if (selectedLaumio && selectedLaumio.y !== text) {
                            selectedLaumio.y = text;
                        }
                    }
                }
            }

        }

        // Color
        Column {
            spacing: 10
            width: parent.width

            LATitle {
                text: "Couleur"
            }

            Column {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Binding {
                    target: view
                    property: "color"
                    value: selectedLaumio ? selectedLaumio.colorCode : "black"
                }

                Rectangle {
                    id: view
                    height: 160
                    width: 160
                    anchors.horizontalCenter: parent.horizontalCenter

                    onColorChanged: {
                        if (selectedLaumio) {
                            selectedLaumio.send_color(ledField.text, color);
                        }
                    }

                    Behavior on color {
                        ColorAnimation {
                            duration: 200
                        }
                    }

                    LALabel {
                        text: view.color
                        anchors.centerIn: parent
                    }
                }

                Row {
                    spacing: 10

                    LALabel {
                        text: "Teinte"
                        width: 70
                        horizontalAlignment: "AlignRight"
                    }

                    Slider {
                        id: hueSlider
                        minimumValue: 0
                        maximumValue: 1
                        onValueChanged: view.color = Qt.hsla(hueSlider.value, 1, satSlider.value, 1)
                        width: 140
                    }

                    LAButton {
                        text: "Noir"
                        width: 70
                        onClicked: {
                            hueSlider.value = 0
                            view.color = "black"
                        }
                    }
                }

                Row {
                    spacing: 10

                    LALabel {
                        text: "Saturation"
                        width: 70
                        horizontalAlignment: "AlignRight"
                    }

                    Slider {
                        id: satSlider
                        value: 0.5
                        minimumValue: 0
                        maximumValue: 1
                        onValueChanged: view.color = Qt.hsla(hueSlider.value, 1, satSlider.value, 1)
                        width: 140
                    }

                    LAButton {
                        text: "Reset"
                        width: 70
                        onClicked: satSlider.value = 0.5
                    }
                }
            }
        }

        // Animations
        Column {
            spacing: 10
            width: parent.width

            LATitle {
                text: "Animations"
            }

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                ComboBox {
                    id: listAnimation
                    model: ListModel {
                        id: animationItem
                        ListElement {
                            text: "Arc-en-ciel"
                            value: "rainbow"
                        }
                        ListElement {
                            text: "Remplissage"
                            value: "colorWipe"
                        }
                    }
                }

                LAButton {
                    text: "Go !"
                    onClicked: selectedLaumio.animate(animationItem.get(listAnimation.currentIndex).value , "black")
                }
            }
        }
    }
}

