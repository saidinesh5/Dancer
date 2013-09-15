import QtQuick 2.0

Image {
    id: dancer
    source: "../images/Speaker.png"

    Image {
        id: treble
        x: 286
        y: 116
        source: "../images/Speaker/Treble.png"
    }

    Image {
        id: mid
        x: 186
        y: 68
        source: "../images/Speaker/Mid.png"
    }

    Image {
        id: bass
        x: 185
        y: 168
        source: "../images/Speaker/Bass.png"
    }
}
