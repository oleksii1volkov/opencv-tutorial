import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import VideoComponents

ApplicationWindow {
    visible: true
    width: 1200
    height: 800
    title: "Dynamic Image Viewer"

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical

        SplitView {
            orientation: Qt.Horizontal
            SplitView.fillHeight: true

            ListView {
                id: listView
                model: imageModel
                delegate: ItemDelegate {
                    text: model.title
                    width: listView.width
                    onClicked: {
                        imageView.source = "image://pixmaps/" + model.id;
                    }
                }

                SplitView.fillWidth: true
            }

            Image {
                id: imageView
                fillMode: Image.PreserveAspectFit

                SplitView.minimumWidth: 600
                SplitView.preferredWidth: 800
                SplitView.maximumWidth: 1000
            }
        }

        WebCamFaceDetectionItem {
            SplitView.minimumHeight: 200
            SplitView.preferredHeight: 400
            SplitView.maximumHeight: 600
            
            Component.onCompleted: play()
        }
    }
}
