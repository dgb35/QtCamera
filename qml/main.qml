import QtQuick 2.6
import QtQuick.Controls 2.0
import QtMultimedia 5.15
import QtQuick.Layouts 1.5
import com.streaming.FrameProvider 1.0

ApplicationWindow {
    id: root
    width: 600
    height: 900
    visible: true

    color: "black"
    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            width: 640
            height: 480

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

        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            width: 250
            height: 60
            color: "black"
            RowLayout {
                anchors.fill: parent
                spacing: 1

                Button {
                    id: start
                    width: 100
                    height: 30
                    text: "Start"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    onClicked: camera.start()
                }
                Button {
                    id: stop
                    width: 100
                    height: 30
                    text: "Stop"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    onClicked: camera.stop()
                }
            }
        }
    }



}