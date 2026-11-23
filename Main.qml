import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: qsTr("Earthquake Dashboard")

    Column {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 24
        spacing: 12

        Label {
            text: qsTr("Earthquake Dashboard")
            font.pixelSize: 32
            font.bold: true
        }

        Label {
            text: qsTr("Most recent event")
            font.pixelSize: 20
            font.bold: true
            topPadding: 16
        }

        Label {
            text: qsTr("Place: ") + latestPlace
        }

        Label {
            text: qsTr("Magnitude: ") + latestMagnitude
        }

        Label {
            text: qsTr("Time: ") + latestTime
        }
    }
}