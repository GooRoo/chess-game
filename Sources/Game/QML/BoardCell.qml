import QtQuick 2.0

Rectangle {
	id: cell

	property int index: model.index
	property int rowIndex: Math.floor(model.index / 8)
	property int columnIndex: model.index % 8
	property BoardCellStyle cellStyle: BoardCellStyle {
		lightColor: "#FFCE9E"
		darkColor: "#B1478B"
	}

	width: squareSize
	height: squareSize

	color: {
		var evenRow = rowIndex % 2;
		return cellStyle.colors[(model.index + evenRow) % cellStyle.colors.length];
	}

	border.width: 0
	border.color: Qt.darker(color)

	Piece {
		rotation: boardRotation
		anchors.fill: parent
		pieceType: modelData
	}
}
