import QtQuick 2.6
import QtQuick.Controls 2.0
import QtMultimedia 5.15
import com.streaming.FrameProvider 1.0

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true

    color: "black"

    Rectangle {
        objectName: "mainPanel"
        anchors.fill: parent;

        FrameProvider {
            id: provider
        }

        color: "transparent"

        VideoOutput {
            id: display
            objectName: "display"
            anchors.fill: parent;

            source: provider
        }
    }

}