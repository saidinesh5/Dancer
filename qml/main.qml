import QtQuick 2.0
import com.monkeybusiness.dancer 1.0

Rectangle {
    id: root
    width: 480
    height: 800

    color: "grey"

    AudioListener{
        id: audioListener
    }

    Dancer {
        id: dancer
        x: 127
        y: 170
        anchors.bottom: parent.bottom
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
