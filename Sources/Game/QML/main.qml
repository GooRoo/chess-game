import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

ApplicationWindow {
	title: qsTr("Chess")
	width: 800
	height: 600
	visible: true
	visibility: Window.Maximized

	Game {
        anchors.fill: parent
    }
}
