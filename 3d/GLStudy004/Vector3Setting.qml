import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

GroupBox{
    id: root

    property real minX  : x.from
    property real maxX  : x.to
    property real valueX: x.value

    property real minY  : y.from
    property real maxY  : y.to
    property real valueY: y.value

    property real minZ  : z.from
    property real maxZ  : z.to
    property real valueZ: z.value

    signal xValueChanged( real value )
    signal yValueChanged( real value )
    signal zValueChanged( real value )

    GridLayout{
        columns: 3

        Text{
            text: "X"
            color: "white"
        }

        Text{
            text: "" + x.value
            color: "white"
        }

        LabeledSlider{
            id: x
            onPositionChanged: {
                root.xValueChanged(value)
            }
            onValueChanged: {
                root.xValueChanged(value)
            }
        }

        Text{
            text: "Y"
            color: "white"
        }

        Text{
            text: "" + y.value
            color: "white"
        }

        LabeledSlider{
            id: y
            onPositionChanged: {
                root.yValueChanged(value)
            }
            onValueChanged: {
                root.yValueChanged(value)
            }
        }

        Text{
            text: "Z"
            color: "white"
        }

        Text{
            text: "" + z.value
            color: "white"
        }

        LabeledSlider{
            id: z
            onPositionChanged: {
                root.zValueChanged(value)
            }
            onValueChanged: {
                root.zValueChanged(value)
            }
        }
    }
}
