import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 1100
    height: 720
    minimumWidth: 820
    minimumHeight: 560
    visible: true
    title: qsTr("Earthquake Dashboard")

    Label {
        anchors.centerIn: parent
        text: qsTr("Earthquake Dashboard")
        font.pixelSize: 28
        font.bold: true
    }
}
