import QtQuick 2.0
import QtQuick.Layouts 1.2

Rectangle {
    id: calculator

    property real fontSize: 20

    width: topLayout.width + fontSize * 2
    height: topLayout.height + fontSize * 2

    SystemPalette { id: activePalette }

    color: activePalette.window

    Model{
        id: calculatorModel
    }

    ColumnLayout{
        id: topLayout
        anchors.centerIn: parent
        spacing: fontSize / 2

        Display{
            id: display1
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: calculatorModel.displayString1
        }

        Display{
            id: display2
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: calculatorModel.displayString2
        }

        GridLayout{
            columnSpacing: fontSize / 2
            rowSpacing: fontSize / 2

            RowLayout{
                id: varousButtonLayout
                Layout.row: 0
                Layout.column: 0
                Layout.fillWidth: true
                Layout.fillHeight: true

                spacing: fontSize / 4

                Button{
                    text: "AC"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    onClicked : {
                        console.log( "button " + text + " clicked !" );
                        calculatorModel.clearAll()
                    }
                }

                Button{
                    text: "C"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    onClicked : {
                        console.log( "button " + text + " clicked !" );
                        calculatorModel.clear()
                    }
                }

                Button{
                    text: "+/-"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    onClicked : {
                        console.log( "button " + text + " clicked !" );
                        calculatorModel.changeSign()
                    }
                }

            }

            ColumnLayout{
                id: operatorLayout
                Layout.row: 0
                Layout.column: 1
                Layout.rowSpan: 2
                Layout.fillWidth: true
                Layout.fillHeight: true

                spacing: fontSize / 4

                Repeater{
                    model: [ "/", "*", "-", "+" ]
                    Button{
                        text: modelData
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        enabled: calculatorModel.operatorEnabled
                        onClicked : {
                            console.log( "button " + text + " clicked !" );
                            calculatorModel.setOperator(text)
                        }
                    }
                }
                Button{
                    text: "="
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    enabled: calculatorModel.equalEnabled
                    onClicked : {
                        console.log( "button " + text + " clicked !" );
                        calculatorModel.calculate()
                    }
                }
            }

            GridLayout{
                id: numberGrid
                Layout.row: 1
                Layout.column: 0
                Layout.fillWidth: true
                Layout.fillHeight: true

                columns: 3
                columnSpacing: fontSize / 4
                rowSpacing: fontSize / 4

                Repeater{
                    model: [ 7,8,9,4,5,6,1,2,3 ]
                    Button{
                        text: "" + modelData
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        onClicked : {
                            console.log( "button " + text + " clicked !" );
                            calculatorModel.addDigit(modelData)
                        }
                    }
                }
                Button{
                    text: "0"
                    Layout.columnSpan: 3
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    onClicked : {
                        console.log( "button " + text + " clicked !" );
                        calculatorModel.addDigit(0)
                    }
                }
            }
        }
    }
}
