#pragma once

namespace chess
{
	static const size_t MaxBoardSize = 8;

	enum class Color
	{
		White,
		Black,
		Undefined
	};

	enum class Step
	{
		Wrong,
		Move,
		Capture
	};

	enum class Direction
	{
		Downward,
		Upward,
		NoMove
	};

	enum class PieceType
	{
		King,
		Queen,
		Rook,
		Knight,
		Bishop,
		Pawn
	};
}
