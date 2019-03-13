import QtQuick 2.0
import "Utils.js" as Utils

Item {
	property string pieceType: "p"

	width: 100
	height: width

	Text {
		id: back
		text: Utils.getPieceSymbol(pieceType.toLowerCase())
		color: Utils.isWhite(pieceType)? "white" : "black"
		anchors.fill: parent
		font.pixelSize: height / 2
		font.family: "Arial"
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
	}

	Text {
		id: outline
		smooth: true
		text: Utils.getPieceSymbol(pieceType.toUpperCase())
		color: Utils.isWhite(pieceType)? "black" : "transparent"
		anchors.fill: back
		font.pixelSize: back.font.pixelSize
		font.family: back.font.family
		horizontalAlignment: back.horizontalAlignment
		verticalAlignment: back.verticalAlignment
	}
}
