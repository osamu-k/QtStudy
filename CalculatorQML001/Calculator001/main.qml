import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import "qml"

Window {
    visible: true
    width: layout.width
    height: layout.height

    ColumnLayout{
        id: layout

        Calculator {
        }
    }
}
