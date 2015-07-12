import QtQuick 2.0
import QtQuick.Layouts 1.2

Rectangle {
    id: game

    property real fontSize: 20

    SystemPalette { id: activePalette }

    color: activePalette.window

    ColumnLayout {
        anchors.fill: parent

        RowLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            id: buttonRow
            spacing: 5

            Button{
                id: startButton
                text: "start"
                onClicked: gameSpace.start()
            }

            Button{
                id: stopButton
                text: "stop"
                onClicked: gameSpace.stop()
            }

            Button{
                id: clearButton
                text: "clear"
                onClicked: gameSpace.clear()
            }

            Button{
                id: quitButton
                text: "quit"
                onClicked: Qt.quit()
            }
        }

        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            GameSpace{
                id: gameSpace
                anchors.fill: parent
            }
        }
    }
}
