import QtQuick 2.0

Rectangle {
    SystemPalette { id: activePalette }

    Item{
        width: parent.width
        anchors { top: parent.top; bottom: toolbar.top }

        Image{
            id: background
            anchors.fill: parent
            source: "pics/background.jpg"
            fillMode: Image.PreserveAspectCrop
        }
    }

    Rectangle{
        id: toolbar
        width: parent.width
        height:30
        anchors { bottom: parent.bottom }

        Button{
            anchors { left: parent.left; verticalCenter: parent.verticalCenter }
            text:  "New Game"
        }

        Text{
            id: score
            anchors { right: parent.right; verticalCenter: parent.verticalCenter }
            text: "Score: "
        }
    }
}

