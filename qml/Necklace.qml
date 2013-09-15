import QtQuick 2.0

RhythmicItem {
    id: necklace

    source: "../images/Dancer/Necklace.png"
    transformOrigin: Item.Top

    Timer {
        interval: animationDuration
        repeat: true
        running: true
        onTriggered: {
            if(parent.state === "" )
                parent.state = 1
            parent.state *= -1
        }
    }

    states: [
        State {
            name: "1"
            PropertyChanges {
                target: necklace
                rotation: animationMagnitude
            }
        },
        State {
            name: "-1"
            PropertyChanges {
                target: necklace
                rotation: -animationMagnitude
            }
        }
    ]
    transitions: [
        Transition {
            from: "*"
            to: "*"
            NumberAnimation { target: necklace; property: "rotation"; duration: animationDuration }
            reversible: true
        }
    ]
}
