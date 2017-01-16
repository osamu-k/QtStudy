import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

GroupBox{
    title: "lighting"

    ColumnLayout{
        GroupBox{
            title: "light position"

            GridLayout{
                columns: 3

                Text{
                    text: "distance"
                    color: "white"
                }

                Text{
                    text: "" + lightDistance.value
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
                    text: "angle-X"
                    color: "white"
                }

                Text{
                    text: "" + lightAngleX.value
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
                    text: "angle-Y"
                    color: "white"
                }

                Text{
                    text: "" + lightAngleY.value
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
        }

        Vector3Setting{
            title: "light direction"
        }
    }
}
