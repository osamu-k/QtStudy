import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import GLStudy 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("OpenGL Study 001")

Flickable{
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    width: settingGrid.width

    contentWidth: settingGrid.width;
    contentHeight: settingGrid.height

    opacity: 0.5

    Grid{
        id: settingGrid
        columns: 2

        Text{
            text: "rotate X"
            color: "white"
        }

        Slider{
            id: rotateX
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 360.0
            value: 0.0
            onPositionChanged: {
                modelRenderer.rotateX = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.rotateX = value;
            }
        }

        Text{
            text: "rotate Y"
            color: "white"
        }

        Slider{
            id: rotateY
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 360.0
            value: 0.0
            onPositionChanged: {
                modelRenderer.rotateY = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.rotateY = value;
            }
        }

        Text{
            text: "rotate Z"
            color: "white"
        }

        Slider{
            id: rotateZ
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 360.0
            value: 0.0
            onPositionChanged: {
                modelRenderer.rotateZ = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.rotateZ = value;
            }
        }

        Text{
            text: "eye distance"
            color: "white"
        }

        Slider{
            id: eyeDistance
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 10.0
            value: 2.0
            onPositionChanged: {
                modelRenderer.eyeDistance = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.eyeDistance = value;
            }
        }

        Text{
            text: "eye angle X"
            color: "white"
        }

        Slider{
            id: eyeAngleX
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 360.0
            value: 0.0
            onPositionChanged: {
                modelRenderer.eyeAngleX = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.eyeAngleX = value;
            }
        }

        Text{
            text: "eye angle Y"
            color: "white"
        }

        Slider{
            id: eyeAngleY
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 360.0
            value: 0.0
            onPositionChanged: {
                modelRenderer.eyeAngleY = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.eyeAngleY = value;
            }
        }

        Text{
            text: "light distance"
            color: "white"
        }

        Slider{
            id: lightDistance
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 10.0
            value: 4.0
            onPositionChanged: {
                modelRenderer.lightDistance = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.lightDistance = value;
            }
        }

        Text{
            text: "light angle X"
            color: "white"
        }

        Slider{
            id: lightAngleX
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 360.0
            value: 0.0
            onPositionChanged: {
                modelRenderer.lightAngleX = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.lightAngleX = value;
            }
        }

        Text{
            text: "light angle Y"
            color: "white"
        }

        Slider{
            id: lightAngleY
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 360.0
            value: 0.0
            onPositionChanged: {
                modelRenderer.lightAngleY = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.lightAngleY = value;
            }
        }

        Text{
            text: "ambeint brightness"
            color: "white"
        }

        Slider{
            id: ambientBlightness
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 1.0
            value: 0.5
            onPositionChanged: {
                modelRenderer.ambientBrightness = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.ambientBrightness = value;
            }
        }

        Text{
            text: "diffuse brightness"
            color: "white"
        }

        Slider{
            id: diffuseBlightness
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 1.0
            value: 0.75
            onPositionChanged: {
                modelRenderer.diffuseBrightness = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.diffuseBrightness = value;
            }
        }

        Text{
            text: "specular brightness"
            color: "white"
        }

        Slider{
            id: specularBlightness
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 1.0
            value: 0.5
            onPositionChanged: {
                modelRenderer.specularBrightness = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.specularBrightness = value;
            }
        }

        Text{
            text: "ambeint Reflection"
            color: "white"
        }

        Slider{
            id: ambientReflection
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 1.0
            value: 0.5
            onPositionChanged: {
                modelRenderer.ambientReflection = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.ambientReflection = value;
            }
        }

        Text{
            text: "diffuse Reflection"
            color: "white"
        }

        Slider{
            id: diffuseReflection
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 1.0
            value: 0.75
            onPositionChanged: {
                modelRenderer.diffuseReflection = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.diffuseReflection = value;
            }
        }

        Text{
            text: "specular Reflection"
            color: "white"
        }

        Slider{
            id: specularReflections
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 1.0
            value: 0.5
            onPositionChanged: {
                modelRenderer.specularReflection = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.specularReflection = value;
            }
        }

        Text{
            text: "shininess"
            color: "white"
        }

        Slider{
            id: shininess
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 100.0
            value: 100.0
            onPositionChanged: {
                modelRenderer.shininess = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.shininess = value;
            }
        }

        Text{
            text: "spot exponent"
            color: "white"
        }

        Slider{
            id: spotExponent
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 100.0
            value: 1.0
            onPositionChanged: {
                modelRenderer.spotExponent = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.spotExponent = value;
            }
        }

        Text{
            text: "cutoff angle"
            color: "white"
        }

        Slider{
            id: cutoffAngle
            snapMode: Slider.SnapAlways
            from: 0.0
            to: 180.0
            value: 180.0
            onPositionChanged: {
                modelRenderer.cutoffAngle = (from + (to - from) * position);
            }
            onValueChanged: {
                modelRenderer.cutoffAngle = value;
            }
        }
    }
}
    ModelRenderer{
        id: modelRenderer
    }
}
