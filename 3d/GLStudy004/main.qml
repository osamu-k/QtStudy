import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: root
    visible: true
    width: 640
    height: 480

        Flickable{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: settingGrid.width

        contentWidth: settingGrid.width;
        contentHeight: settingGrid.height

        opacity: 0.7

        LightSettings{
        }

/*
        Grid{
            id: settingGrid
            columns: 2
            spacing: 5

            Text{
                text: "light distance"
                color: "white"
            }

            LabeledSlider{
                id: lightDistance
                from: 0.0
                to: 10.0
                value: mainView.lightDistance
                onPositionChanged: {
                    mainView.lightDistance = (from + (to - from) * position);
                }
                onValueChanged: {
                    mainView.lightDistance = value;
                }
            }

            Text{
                text: "light angle X"
                color: "white"
            }

            LabeledSlider{
                id: lightAngleX
                from: -180.0
                to: 180.0
                value: mainView.lightAngleX
                onPositionChanged: {
                    mainView.lightAngleX = (from + (to - from) * position);
                }
                onValueChanged: {
                    mainView.lightAngleX = value;
                }
            }

            Text{
                text: "light angle Y"
                color: "white"
            }

            LabeledSlider{
                id: lightAngleY
                from: -180.0
                to: 180.0
                value: mainView.lightAngleY
                onPositionChanged: {
                    mainView.lightAngleY = (from + (to - from) * position);
                }
                onValueChanged: {
                    mainView.lightAngleY = value;
                }
            }
        }
*/
    }
}
