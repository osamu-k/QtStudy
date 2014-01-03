/****************************************************************************
**
** Copyright (C) 2014 Osamu Kobayashi.
** Contact: osamu-k@arion.ocn.ne.jp
**
** This file may be used under the terms of
** the GNU General Public License version 3.0
** as published by the Free Software Foundation
** http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

import QtQuick 2.0

Rectangle {
    id: game
    color: "lightYellow"

    Row{
        id: buttonRow
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 5
        spacing: 5

        Button{
            id: startButton
            width: 50
            height: 24
            color: "green"
            textColor: "white"
            text: "start"
            onClicked: gameSpace.start()
        }

        Button{
            id: stopButton
            width: 50
            height: 24
            color: "blue"
            textColor: "white"
            text: "stop"
            onClicked: gameSpace.stop()
        }

        Button{
            id: clearButton
            width: 50
            height: 24
            color: "yellow"
            textColor: "black"
            text: "clear"
            onClicked: gameSpace.clear()
        }

        Button{
            id: quitButton
            width: 50
            height: 24
            color: "red"
            textColor: "white"
            text: "quit"
            onClicked: Qt.quit()
        }
    }

    GameSpace{
        id: gameSpace
        anchors.top: buttonRow.bottom
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
        clip: true
    }
}
