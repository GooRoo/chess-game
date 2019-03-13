import QtQuick 2.0
import QtQuick.Dialogs 1.2
import "Chess"

Rectangle {
	id: container
	width: 640
	height: 480

	GameScreen {
		id: gameScreen
		anchors.fill: parent

		Keys.onEscapePressed: {
			startScreen.toggle();
		}
	}

	StartScreen {
		id: startScreen
		anchors.fill: parent
		source: gameScreen

		onNewGameClicked: {
			startScreen.toggle();
			gameScreen.focus = true;
			boardModel.newGame();
		}
		onSaveGameClicked: notImplementedYet.open()
		onLoadGameClicked: {
			startScreen.toggle();
			loadScreen.toggle();
			loadScreen.focus = true;
			notImplementedYet.open();
		}
		onExitClicked: Qt.quit()

		focus: true

		MessageDialog {
			id: notImplementedYet
			title: "Sorry"
			text: "This functionality is not implemented yet"
			icon: StandardIcon.Warning
			onAccepted: {
				if (loadScreen.focus)
				{
					loadScreen.toggle();
					startScreen.toggle();
					startScreen.focus = true;
				}
			}
		}
	}

	LoadScreen {
		id: loadScreen
		source: gameScreen
		anchors.fill: parent
		state: "off"

		Keys.onEscapePressed: {
			loadScreen.toggle();
			startScreen.toggle();
			startScreen.focus = true;
		}
	}
}
