.pragma library

function getPieceSymbol(pt) {
	var pieces = {
		"k": "♚",
		"q": "♛",
		"r": "♜",
		"b": "♝",
		"n": "♞",
		"p": "♟",
		"K": "♔",
		"Q": "♕",
		"R": "♖",
		"B": "♗",
		"N": "♘",
		"P": "♙",
		"" : ""
	};
	return pieces[pt];
}

function isWhite(pt) {
	return pt !== pt.toLowerCase();
}

function invertedColor(c) {
	return Qt.rgba(1. - c.r, 1. - c.g, 1. - c.b, c.a);
}

function getInvertedPieceSymbol(pt) {
	var newPt = isWhite(pt)? pt.toLowerCase() : pt.toUpperCase();
	return getPieceSymbol(newPt);
}

function isHalfInvertedColor(c) {
	return c.r > .5 && c.g > .5 && c.b > .5;
}
