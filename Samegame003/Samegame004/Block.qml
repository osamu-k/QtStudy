import QtQuick 2.0

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

    states: [
        State {
            name: "AliveState"
            when: spawned && ! dying
            PropertyChanges { target: image; opacity: 1 }
        },
        State {
            name: "DeathState"
            when: dying
            PropertyChanges { target: image; opacity: 0 }
            StateChangeScript { script: block.destroy(1000) }
        }
    ]
}

