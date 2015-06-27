import QtQuick 2.0

Rectangle {
    id: container

    property string inputText: textInput.text
    signal closed
    signal accepted

    width: dialogText.width + textInput.width + 20
    height: dialogText.height + 20
    opacity: 0
    visible: opacity > 0

    function show( text )
    {
        dialogText.opacity = 1
        dialogText.text = text
        container.opacity = 1
        textInput.opacity = 0

        console.log( "dialogText.width=" + dialogText.width )
        console.log( "container.width=" + container.width )
    }

    function showWithInput( text )
    {
        dialogText.text = text
        container.opacity = 1
        textInput.opacity = 1
        textInput.text = ""
        textInput.focus = true
    }

    function hide()
    {
        textInput.focus = false
        container.opacity = 0
        container.closed()
    }

    Text{
        id: dialogText
        anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
        text: ""
    }
    TextInput{
        id: textInput
        anchors { verticalCenter: parent.verticalCenter; left: dialogText.right }
        width: 80
        text: ""

        onAccepted: {
            container.hide()
            container.accepted()
        }
    }
    MouseArea{
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            hide()
        }
    }
}
