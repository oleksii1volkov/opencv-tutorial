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

    WebCamObjectTrackingItem {
        anchors.fill: parent
        Component.onCompleted: play()
    }
}
