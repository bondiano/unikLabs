import QtQuick 2.0

Rectangle {
    id: button

    property bool checked: false
    property alias text : buttonText.text
    Accessible.name: text
    Accessible.description: "This button does " + text
    Accessible.role: Accessible.Button
    Accessible.onPressAction: {
        button.clicked()
    }

    signal clicked

    width: buttonText.width + 20
    height: 30
    color: button.focus ? "#90A4AE" : "#607D8B"
    antialiasing: true

    Text {
        id: buttonText
        text: parent.description
        anchors.centerIn: parent
        font.pixelSize: parent.height * .5
        font.bold: true
        color: "white"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: parent.clicked()
    }

    Keys.onSpacePressed: clicked()
}
