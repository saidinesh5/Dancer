import QtQuick 2.0

Image {
    id: dancer
    source: "../images/Speaker/SpeakerBase.png"

    SpeakerMembrane {
        id: treble
        x: 286
        y: 116
        source: "../images/Speaker/Treble.png"
        value: ( audioListener.data["left"]["octave6"] + audioListener.data["left"]["octave7"])
    }

    SpeakerMembrane {
        id: mid
        x: 186
        y: 68
        source: "../images/Speaker/Mid.png"
        value: audioListener.data["left"]["octave3"] + audioListener.data["left"]["octave4"] + audioListener.data["left"]["octave5"]
    }

    SpeakerMembrane {
        id: bass
        x: 185
        y: 168
        source: "../images/Speaker/Bass.png"
        value: audioListener.data["left"]["octave0"] + audioListener.data["left"]["octave1"]+ audioListener.data["left"]["octave2"]
    }
}
