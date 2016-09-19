import QtQuick 2.7
import QtQuick.Controls 2.0
import QML3D001 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    PinchArea{
        anchors.fill: parent

        onPinchStarted: {
        }
        onPinchUpdated: {
            renderer.pinched( pinch.scale / pinch.previousScale );
        }
        onPinchFinished: {
            renderer.pinched( pinch.scale / pinch.previousScale );
        }

        MouseArea {
            anchors.fill: parent

            onPressed: {
                renderer.mousePressed( mouse.x, mouse.y );
            }
            onPositionChanged: {
                renderer.mouseMoved( mouse.x, mouse.y, mouse.buttons & Qt.LeftButton )
            }
            onReleased: {
                renderer.mouseReleased( mouse.x, mouse.y, mouse.buttons & Qt.LeftButton )
            }
        }
    }

    Row{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        opacity: 0.5

        CheckBox{
            id: checkUseTexture
            text: "<font color=\"white\">Use Texture</font>"
            checked: renderer.useTexture
            onCheckedChanged: {
                renderer.useTexture = checked
            }
        }

        CheckBox{
            id: checkUseLight
            text: "<font color=\"white\">UseLight</font>"
            checked: renderer.useLight
            onCheckedChanged: {
                renderer.useLight = checked
            }
        }

        CheckBox{
            id: checkUseBuffer
            text: "<font color=\"white\">UseBuffer</font>"
            checked: renderer.useBuffer
            onCheckedChanged: {
                renderer.useBuffer = checked
            }
        }
    }

    Column{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        opacity: 0.5

//        Slider{
//            id: sliderAlpha
//            from: -180.0
//            to: 180.0
//            value: 25.0
//            onPositionChanged: {
//                console.log( "alpha changed: " + (from + (to - from) * position ) )
//                renderer.alpha = (from + (to - from) * position);
//            }
//            onValueChanged: {
//                console.log( "alpha changed: " + value )
//                renderer.alpha = value;
//            }
//        }
//        Slider{
//            id: sliderBeta
//            from: -180.0
//            to: 180.0
//            value: -25.0
//            onPositionChanged: {
//                console.log( "beta changed: " + (from + (to - from) * position ) )
//                renderer.beta = (from + (to - from) * position);
//            }
//            onValueChanged: {
//                console.log( "beta changed: " + value )
//                renderer.beta = value;
//            }
//        }
//        Slider{
//            id: sliderDistance
//            snapMode: Slider.SnapAlways
//            from: 0.0
//            to: 10.0
//            value: 5.0
//            onPositionChanged: {
//                console.log( "distane changed: " + (from + (to - from) * position ) )
//                renderer.distance = (from + (to - from) * position);
//            }
//            onValueChanged: {
//                console.log( "distane changed: " + value )
//                renderer.distance = value;
//            }
//        }
        Slider{
            id: sliderLightAngle
            snapMode: Slider.SnapAlways
            from: -180.0
            to: 180.0
            value: 0.0
            onPositionChanged: {
                console.log( "distane changed: " + (from + (to - from) * position ) )
                renderer.lightAngle = (from + (to - from) * position);
            }
            onValueChanged: {
                console.log( "distane changed: " + value )
                renderer.lightAngle = value;
            }
        }
    }

    Renderer3D{
        id: renderer
//        alpha:sliderAlpha.value
//        beta:sliderBeta.value
//        distance: sliderDistance.value
    }
}
