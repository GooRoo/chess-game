#pragma once

#include "Chess/Common.hpp"
#include "Chess/Board.hpp"

namespace chess
{
	class Transition;

	class Piece
	{
	public:
		Piece(const Board * board);
		virtual ~Piece();

		virtual Step check(const Transition & move) const = 0;
		virtual char letter() const = 0;
		virtual Color color() const = 0;
		virtual PieceType type() const = 0;

		const Board & board() const;

	private:
		const Board * const m_board;
	};
}
