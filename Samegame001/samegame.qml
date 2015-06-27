import QtQuick 2.4
import QtQuick.Window 2.2

import "samegame.js" as SameGame

Window {
    id: screen
    width: 490
    height: 720
    visible: true

    SystemPalette{
        id: activePalette
    }

    Item{
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: toolbar.top
        Image{
            id: background
            anchors.fill: parent
            source: "pics/background.jpg"
            fillMode: Image.PreserveAspectCrop
        }
        Item{
            id: gameCanvas
            property int score: 0
            property int blockSize: 40

            width: parent.width - (parent.width % blockSize)
            height: parent.height - (parent.height % blockSize)
            anchors.centerIn: parent

            MouseArea{
                anchors.fill: parent
                onClicked: SameGame.handleClick(mouse.x,mouse.y)
            }
        }
    }

    Dialog{
        id: dialog
        anchors.centerIn: parent
        z: 100
    }

    Dialog{
        id: nameInputDialog
        anchors.centerIn: parent
        z: 100
        onClosed:{
            if( nameInputDialog.inputText != "" ){
                SameGame.saveHighScore(nameInputDialog.inputText)
            }
        }
    }

    Rectangle{
        id: toolbar
        width: parent.width
        height: 30
        anchors.bottom: parent.bottom
        color: activePalette.window

        Button{
            anchors { left: parent.left; verticalCenter: parent.verticalCenter }
            text: "New Game"
            onClicked: SameGame.startNewGame()
        }

        Text{
            id: score
            anchors {right: parent.right; verticalCenter: parent.verticalCenter}
            text: "Score: " + gameCanvas.score
        }
    }
}

