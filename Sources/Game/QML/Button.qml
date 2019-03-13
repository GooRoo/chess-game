import QtQuick 2.0
import QtQuick.Controls 1.2 as QQC
import QtQuick.Controls.Styles 1.2

QQC.Button {
	width: 100
	height: 62

	style: ButtonStyle {
		background: Rectangle {
			implicitWidth: 200
			implicitHeight: 100
			border.color: "orange"
			border.width: 5
			radius: 10
			color: control.hovered? "orange" : "transparent"
		}
		label: Text {
			color: control.hovered? "white" : "orange"
			text: control.text
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			font.family: "Segoe UI"
			font.pixelSize: height / 2
			font.bold: true
		}
	}
}

