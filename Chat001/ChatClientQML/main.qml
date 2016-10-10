import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 400
    height: 400
    title: qsTr("Chat client")

    Rectangle{
        anchors.fill: parent
        color:"gray"

        Rectangle{
            id: areaLog
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: areaInput.top
            color:"lightgray"

            TextEdit{
                id: textLog
                anchors.fill: parent
            }
        }

        Rectangle{
            id: areaInput
//            anchors.top: areaLog.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: rowButtons.top
            color:"white"
            height: 100

            TextEdit{
                id: textInput
                anchors.fill: parent
            }
        }

        Row{
            id: rowButtons
//            anchors.top: areaInput.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 30

            Button{
                id: buttonClear
                text: "clear"
                onClicked: {
                    textInput.text = ""
                }
            }
            Button{
                id: buttonSend
                text: "send"
                onClicked: {
                    textLog.append( textInput.text )
                }
            }
        }
    }
}
