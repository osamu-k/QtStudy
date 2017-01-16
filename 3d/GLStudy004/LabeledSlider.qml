import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item{
    id: root
    width: rowLayout.width
    height: rowLayout.height

    property real from : slider.from
    property real to   : slider.to
    property real value: slider.value

    signal positionChanged( real position )

    RowLayout {
        id: rowLayout

        Text{
            text: "" + root.from
        }

        Slider{
            id: slider
            snapMode: Slider.SnapAlways

            Layout.fillWidth: true

            onPositionChanged: {
                root.positionChanged(from + (to - from) * position)
            }
            onValueChanged: {
                root.valueChanged(value)
            }
        }

        Text{
            text: "" + root.to
        }
    }
}
