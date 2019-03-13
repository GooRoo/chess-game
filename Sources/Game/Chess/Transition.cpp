#include "Chess/Transition.hpp"

#include "Chess/Board.hpp"
#include "Chess/Piece.hpp"
#include "Chess/Position.hpp"

#include <cstdlib>

using namespace chess;

Transition::Transition(const Board & board, const Position & from, const Position & to)
	: m_board{board}
	, m_from{from}
	, m_to{to}
{}

int Transition::horizontalLength() const
{
	return std::abs(m_from.column() - m_to.column());
}

int Transition::verticalLength() const
{
	return std::abs(m_from.row() - m_to.row());
}

const Position & Transition::from() const
{
	return m_from;
}

const Position & Transition::to() const
{
	return m_to;
}

const PiecePtr Transition::piece() const
{
	return board()[m_from];
}

const PiecePtr Transition::target() const
{
	return board()[m_to];
}

Color Transition::pieceColor() const
{
	return getColor(piece());
}

Color Transition::targetColor() const
{
	return getColor(target());
}

Color Transition::getColor(PiecePtr p) const
{
	if (!p)
		return Color::Undefined;
	else
		return p->color();
}

const Board & Transition::board() const
{
	return m_board;
}
