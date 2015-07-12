import QtQuick 2.0

Rectangle {
    property string text: "button"
    signal clicked

    id: container

    width: buttonText.contentWidth + buttonText.font.pixelSize * 2
    height: buttonText.contentHeight + buttonText.font.pixelSize
    radius: 5
    border { width: 1;  color: Qt.darker(activePalette.button) }
    antialiasing: true

    opacity: enabled ? 1.0 : 0.5

    gradient: Gradient{
        GradientStop{
            position: 0.0
            color: {
                if(mouseArea.pressed)
                   return activePalette.dark
                else
                    return activePalette.light
            }
        }
        GradientStop{
            position: 1.0
            color: activePalette.button
        }
    }

    Text{
        id: buttonText
        anchors.centerIn: parent
        text: container.text
        font.pointSize: calculator.fontSize
        color: activePalette.buttonText
    }

    MouseArea{
        id: mouseArea
        anchors.fill: parent
        onClicked : container.clicked()
    }
}
