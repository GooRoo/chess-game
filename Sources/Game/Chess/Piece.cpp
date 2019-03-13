#include "Chess/Piece.hpp"

using namespace chess;

Piece::Piece(const Board * board)
	: m_board{board}
{}

Piece::~Piece()
{}

const Board & Piece::board() const
{
	return *m_board;
}
