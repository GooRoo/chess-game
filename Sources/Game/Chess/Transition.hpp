#pragma once

#include "Chess/Common.hpp"
#include "Chess/Board.hpp"

namespace chess
{
	class Position;

	class Transition
	{
		friend class BoardT<>;
		Transition(const Board & board, const Position & from, const Position & to);
	public:
		~Transition() = default;

		int horizontalLength() const;
		int verticalLength() const;

		const Position & from() const;
		const Position & to() const;

		const PiecePtr piece() const;
		const PiecePtr target() const;
		const Board & board() const;

		Color pieceColor() const;
		Color targetColor() const;

	private:
		Color getColor(PiecePtr p) const;

	private:
		const Board & m_board;

		const Position & m_from;
		const Position & m_to;
	};
}
