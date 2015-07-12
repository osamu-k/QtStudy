import QtQuick 2.0

Rectangle {
    property string text: ""

    id: container

//    width: displayText.contentWidth + displayText.font.pixelSize * 2
    height: displayText.contentHeight + displayText.font.pixelSize
    color: "white"
    border.color: activePalette.dark

    Text{
        id: displayText
        anchors.fill: parent
        anchors.rightMargin: font.pixelSize
        text: container.text
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.pointSize: calculator.fontSize
    }
}

