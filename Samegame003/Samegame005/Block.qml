import QtQuick 2.0
import QtQuick.Particles 2.0

Item {
    id: block

    property int type: 0
    property bool spawned: false
    property bool dying: false

    Behavior on x {
        enabled: block.spawned
        SpringAnimation { spring: 2; damping: 0.2 }
    }

    Behavior on y {
        SpringAnimation { spring: 2; damping: 0.2 }
    }

    Image{
        id: image
        anchors.fill: parent
        source:{
            if( type == 0 )
                return "pics/redStone.png"
            else if( type == 1 )
                return "pics/blueStone.png"
            else
                return "pics/greenStone.png"
        }
        opacity: 0
        Behavior on opacity {
            NumberAnimation { properties: "opacity"; duration: 200 }
        }
    }

    ParticleSystem {
        id: sys
        anchors.centerIn: parent

        ImageParticle{
            source:{
                if( type == 0 )
                    return "pics/redStar.png"
                else if( type == 1 )
                    return "pics/blueStar.png"
                else
                    return "pics/greenStar.png"
            }
            rotationVelocityVariation: 360
        }

        Emitter{
            id: particles
            anchors.centerIn: parent
            emitRate: 0
            lifeSpan: 700
            velocity: AngleDirection { angleVariation: 360; magnitude: 80; magnitudeVariation: 40 }
            size: 16
        }
    }

    states: [
        State {
            name: "AliveState"
            when: spawned && ! dying
            PropertyChanges { target: image; opacity: 1 }
        },
        State {
            name: "DeathState"
            when: dying
            StateChangeScript { script: particles.burst(50) }
            PropertyChanges { target: image; opacity: 0 }
            StateChangeScript { script: block.destroy(1000) }
        }
    ]
}

