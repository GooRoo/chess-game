import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQml.Models 2.1
import "Utils.js" as Utils

Rectangle {
	id: container
	width: 640
	height: 480

	color: board.color

	Board {
		id: board
		width: Math.min(container.width, container.height)
		anchors.centerIn: parent
		rotation: (rotateBoard.checked && !boardModel.whitesTurn)? 180 : 0

		Behavior on rotation {
			NumberAnimation {
				duration: 500
				easing.type: Easing.InOutQuad
			}
		}
	}

	ListModel {
		id: historyModel
	}

	ListView {
		id: historyView

		property var lastMove: history.lastMove

		onLastMoveChanged: {
			if (lastMove.isEmpty)
				historyModel.clear();
			else
			{
				historyModel.append({
					"whitePiece": lastMove.whitePiece,
					"whiteFrom": lastMove.whiteFrom,
					"whiteTo": lastMove.whiteTo,
					"whiteCapture": lastMove.whiteCapture,
					"blackPiece": lastMove.blackPiece,
					"blackFrom": lastMove.blackFrom,
					"blackTo": lastMove.blackTo,
					"blackCapture": lastMove.blackCapture
				});
			}
		}

		clip: true

		model: historyModel
		delegate: Text {
			color: Utils.invertedColor(board.color)
			text: {
				var f = Utils.isHalfInvertedColor(color)? Utils.getInvertedPieceSymbol : Utils.getPieceSymbol;
				var delimW = model.whiteCapture? "x" : "—";
				var delimB = model.blackCapture? "x" : "—";

				return (model.index + 1) + ". " +
					f(model.whitePiece) + model.whiteFrom + delimW + model.whiteTo + " " +
					f(model.blackPiece) + model.blackFrom + delimB + model.blackTo;
			}

			width: ListView.view.width - 10
			height: 20
			font.pixelSize: 16
			horizontalAlignment: Text.AlignRight
		}
		anchors {
			left: board.right
			top: parent.top
			right: parent.right
			bottom: parent.bottom
		}
	}

	CheckBox {
		id: rotateBoard
		checked: false
		text: "Rotate board"
		anchors {
			left: parent.left
			leftMargin: 5
			bottom: parent.bottom
		}
	}

	Text {
		text: "Press Esc to open menu"
		anchors {
			right: parent.right
			rightMargin: 5
			bottom: parent.bottom
		}
		font.pointSize: 12
		font.italic: true
		color: Utils.invertedColor(board.color)
	}

	state: boardModel.whitesTurn? "whitesTurn" : "blacksTurn"
	states: [
		State {
			name: "whitesTurn"
			PropertyChanges {
				target: board
				color: "white"
			}
		},
		State {
			name: "blacksTurn"
			PropertyChanges {
				target: board
				color: "black"
			}
		}
	]
}
