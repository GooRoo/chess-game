import QtQuick 2.0
import QtGraphicalEffects 1.0
import "Utils.js" as Utils

Rectangle {
	id: container

	property int squareSize: Math.min(width, height) / 10
	property bool viewOnly: false

	property alias boardRotation: container.rotation

	width: 600
	height: width

	Row {
		id: topGrid

		height: squareSize
		anchors {
			top: parent.top
			left: parent.left
			right: parent.right
		}

		Repeater {
			model: 10
			delegate: horizontalCaptions
		}
	}

	Row {
		id: bottomGrid

		height: squareSize
		anchors {
			bottom: parent.bottom
			left: parent.left
			right: parent.right
		}

		Repeater {
			model: 10
			delegate: horizontalCaptions
		}
	}

	Column {
		id: leftGrid

		width: squareSize
		anchors {
			top: topGrid.bottom
			left: parent.left
			bottom: parent.bottom
		}

		Repeater {
			model: 8
			delegate: verticalCaptions
		}
	}

	Column {
		id: rightGrid

		width: squareSize
		anchors {
			top: topGrid.bottom
			right: parent.right
			bottom: parent.bottom
		}

		Repeater {
			model: 8
			delegate: verticalCaptions
		}
	}

	Item {
		id: board

		anchors {
			top: topGrid.bottom
			left: leftGrid.right
			right: rightGrid.left
			bottom: bottomGrid.top
		}

		Grid {
			id: grid
			anchors.fill: parent
			columns: 8
			Repeater {
				model: boardModel.pieces //grid.columns * grid.columns
				delegate: BoardCell {
					id: cell

					property bool selected: false

					states: [
						State {
							name: ""
							PropertyChanges {
								target: cell
								border.width: 0
							}
						},
						State {
							name: "hovered"
							when: index == mouseArea.lastIndex && !selected
							PropertyChanges {
								target: cell
								border.width: 10
								border.color: Qt.darker(color)
							}
						},
						State {
							name: "selected"
							when: selected
							PropertyChanges {
								target: cell
								border.width: 10
								border.color: "green"
							}
						},
						State {
							name: "hoveredFail"
							PropertyChanges {
								target: cell
								border.width: 10
								border.color: "red"
							}
						},
						State {
							name: "hoveredCorrect"
							PropertyChanges {
								target: cell
								border.width: 10
								border.color: "lightgreen"
							}
						}

					]
				}
			}
		}

		Rectangle {
			anchors {
				left: grid.left
				top: grid.top
			}
			width: squareSize * grid.columns
			height: squareSize * grid.columns

			color: "transparent"
			border.color: Qt.darker("#D18B47")
			border.width: 2
		}
	}

	Component {
		id: horizontalCaptions
		Text {
			rotation: boardRotation
			width: squareSize
			height: squareSize
			color: viewOnly? "orange" : Utils.invertedColor(container.color)
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			text: {
				var t = ["", "a", "b", "c", "d", "e", "f", "g", "h", ""];
				return t[index];
			}
			font.pixelSize: squareSize / 2
		}
	}

	Component {
		id: verticalCaptions
		Text {
			rotation: boardRotation
			width: squareSize
			height: squareSize
			color: viewOnly? "orange" : Utils.invertedColor(container.color)
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			text: 8 - index
			font.pixelSize: squareSize / 2
		}
	}

	Behavior on color {
		ColorAnimation { duration: 400 }
	}

	MouseArea {
		id: mouseArea

		property BoardCell activeCell
		property BoardCell lastCell
		property int lastIndex: lastCell.index
		property string lastCellPreviousState

		enabled: !viewOnly
		anchors.fill: board
		hoverEnabled: true

		onPositionChanged: {
			var it = grid.childAt(mouse.x, mouse.y);
			if (it.index !== lastIndex) {
				if (activeCell && activeCell != lastCell)
				{
					lastCell.state = lastCellPreviousState;
				}
				lastCell = it;
				console.debug(lastCell.rowIndex + ", " + lastCell.columnIndex);

				if (activeCell)
				{
					var correct = boardModel.tryMove(activeCell.rowIndex, activeCell.columnIndex, lastCell.rowIndex, lastCell.columnIndex);
					lastCellPreviousState = lastCell.state;
					lastCell.state = correct? "hoveredCorrect" : "hoveredFail";
				}
			}
		}

		onClicked: {
			var it = grid.childAt(mouse.x, mouse.y);

			if (!activeCell)
			{
				activeCell = it;
				activeCell.selected = true;
			}
			else if (it.index !== activeCell.index) {
				activeCell.selected = false;
				var success = boardModel.makeMove(activeCell.rowIndex, activeCell.columnIndex, it.rowIndex, it.columnIndex);
				activeCell = null;
				if (!success)
				{
					activeCell = it;
					activeCell.selected = true;
				}
			}
			else {
				activeCell.selected = false;
				activeCell = null;
			}
		}
	}
}
