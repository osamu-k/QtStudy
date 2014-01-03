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

Rectangle{
    id: root
    radius: 5
    property alias text: buttonText.text
    property alias textColor: buttonText.color
    property bool pressed: false
    signal clicked()

    Text{
        id: buttonText
        anchors.fill: parent
        font.pixelSize: 20
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Rectangle{
        id: shadow
        anchors.fill: parent
        radius: parent.radius
        color: "black"
        opacity: parent.pressed ? 0.5 : 0
    }

    MouseArea{
        anchors.fill: parent
        onPressed: parent.pressed = true
        onReleased: parent.pressed = false
        onCanceled: parent.pressed = false
        onClicked: parent.clicked()
    }
}
