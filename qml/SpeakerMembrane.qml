import QtQuick 2.0

Image {
    id: membrane
    property real value: 0

    scale: 1 + Math.min(0.2,value)

    Behavior on scale {
        NumberAnimation {
            duration: 200;
        }
    }

}
