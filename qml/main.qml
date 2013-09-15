import QtQuick 2.0
import com.monkeybusiness.dancer 1.0

Rectangle {
    id: root
    width: 800
    height: 480

    color: "grey"

    AudioListener{
        id: audioListener
    }

    Speaker {
        id: leftSpeaker
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin:  10
        anchors.bottomMargin: 10
    }

    Dancer {
        id: dancer
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10
    }

    Text {
        text: qsTr("Current BPM: ") + Math.round(audioListener.bpm*100)/100
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

}
