import QtQuick 2.0
import "samegame.js" as SameGame

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

        Item{
            id: gameCanvas
            anchors.centerIn: parent
            property int score: 0
            property int blockSize: 40
            property int maxColumn: Math.floor(parent.width / blockSize)
            property int maxRow: Math.floor(parent.height / blockSize)

            width: maxColumn * blockSize
            height: maxRow * blockSize

            MouseArea{
                anchors.fill: parent
                onClicked: SameGame.handleClick( mouse.x, mouse.y )
            }
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
            onClicked: SameGame.startNewGame(
                                    gameCanvas,
                                    gameCanvas.maxColumn,
                                    gameCanvas.maxRow,
                                    gameCanvas.blockSize )
        }

        Text{
            id: score
            anchors { right: parent.right; verticalCenter: parent.verticalCenter }
            text: "Score: "
        }
    }
}

