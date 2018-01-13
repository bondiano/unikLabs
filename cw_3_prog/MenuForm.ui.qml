import QtQuick 2.4

Item {
    id: menuForm
    width: 640
    height: 480

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 640
        height: 480
        color: "#212121"
    }
    ListView {
        id: listView
        x: 0
        y: 0
        width: 640
        height: 480
        antialiasing: false
        orientation: ListView.Vertical
        flickableDirection: Flickable.HorizontalAndVerticalFlick
        transformOrigin: Item.Top
        model: ListModel {
            ListElement {
                name: qsTr("1. Добавить несколько случайных записей.")
            }

            ListElement {
                name: qsTr("1. Добавить несколько случайных записей.")
            }
        }

        delegate: Item {
            width: 80
            height: 40
            Row {
                id: row
                Button {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                }
                spacing: 5
            }
        }
    }
}
