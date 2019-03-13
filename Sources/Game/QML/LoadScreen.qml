import QtQuick 2.0
import QtQuick.Layouts 1.1

OverlayScreen {
	id: screen

	width: 400
	height: 400

	RowLayout {
		anchors.fill: parent
		anchors.margins: 50

		Rectangle {
			id: savesList
			Layout.preferredWidth: parent.width * 0.38 // golden ratio :)
			Layout.fillHeight: true
//			anchors {
//				top: parent.top
//				bottom: parent.bottom
//			}

			color: "red"
		}

		ColumnLayout {
			id: saveDetails
			Layout.fillWidth: true
			Layout.fillHeight: true

//			anchors {
//				top: parent.top
//				bottom: parent.bottom
//			}

			Item {
				Layout.fillHeight: true
				Layout.fillWidth: true
				anchors.left: parent.left
				anchors.right: parent.right

				Board {
					width: Math.min(parent.width, parent.height)
					anchors.centerIn: parent
					viewOnly: true
					color: "transparent"
				}
			}

			Rectangle {
				Layout.preferredHeight: parent.height * 0.38
				Layout.fillWidth: true
				color: "cyan"
			}
		}
	}
}

