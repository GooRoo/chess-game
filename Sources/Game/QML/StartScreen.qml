import QtQuick 2.0
import QtQuick.Layouts 1.1

OverlayScreen {
	id: screen

	signal newGameClicked
	signal saveGameClicked
	signal loadGameClicked
	signal exitClicked

	ColumnLayout {
		anchors.fill: parent
		anchors.topMargin: screen.height / 5
		anchors.bottomMargin: screen.height / 5

		Button {
			text: "New Game"
			Layout.minimumWidth: screen.width / 5
			Layout.minimumHeight: screen.height / 10

			Layout.alignment: Qt.AlignCenter

			onClicked: newGameClicked()
		}

		Button {
			text: "Save Game"
			Layout.minimumWidth: screen.width / 5
			Layout.minimumHeight: screen.height / 10

			Layout.alignment: Qt.AlignCenter

			onClicked: saveGameClicked()
		}

		Button {
			text: "Load Game"
			Layout.minimumWidth: screen.width / 5
			Layout.minimumHeight: screen.height / 10

			Layout.alignment: Qt.AlignCenter

			onClicked: loadGameClicked()
		}

		Button {
			text: "Exit"
			Layout.minimumWidth: screen.width / 5
			Layout.minimumHeight: screen.height / 10

			Layout.alignment: Qt.AlignCenter

			onClicked: exitClicked()
		}
	}
}
