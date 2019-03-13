#include "Chess/BoardModel.hpp"

#include "Chess/Position.hpp"
#include "Chess/Piece.hpp"

using namespace chess;

BoardModel::BoardModel(QObject *parent)
	: QObject{parent}
	, m_whitesTurn{true}
	, m_board{nullptr}
{
	m_pieces << "r" << "n" << "b" << "q" << "k" << "b" << "n" << "r"
			  << "p" << "p" << "p" << "p" << "p" << "p" << "p" << "p"
			  << ""  << ""  << ""  << ""  << ""  << ""  << ""  << ""
			  << ""  << ""  << ""  << ""  << ""  << ""  << ""  << ""
			  << ""  << ""  << ""  << ""  << ""  << ""  << ""  << ""
			  << ""  << ""  << ""  << ""  << ""  << ""  << ""  << ""
			  << "P" << "P" << "P" << "P" << "P" << "P" << "P" << "P"
			  << "R" << "N" << "B" << "Q" << "K" << "B" << "N" << "R";
}

BoardModel::~BoardModel()
{

}

QStringList BoardModel::pieces() const
{
	return m_pieces;
}

bool BoardModel::whitesTurn() const
{
	return m_whitesTurn;
}

void BoardModel::newGame()
{
	emit newGameRequested();
}

bool BoardModel::tryMove(int x1, int y1, int x2, int y2) const
{
	if (!m_board)
		return false;

	return m_board->tryMove(Position{x1, y1}, Position{x2, y2}) != Step::Wrong;
}

bool BoardModel::makeMove(int x1, int y1, int x2, int y2)
{
	if (!m_board)
		return false;

	return m_board->makeMove(Position{x1, y1}, Position{x2, y2}) != Step::Wrong;
}

void BoardModel::onInitialized()
{
	m_pieces.clear();

	for (int i = 0; i < m_board->size(); i++)
	{
		for (int j = 0; j < m_board->size(); j++)
		{
			auto piece = (*m_board)[Position{i, j}];
			if (!piece)
				m_pieces << "";
			else
				m_pieces << QString{piece->letter()};
		}
	}
	emit piecesChanged(m_pieces);
}

void BoardModel::onTurnChange(Color color)
{
	m_whitesTurn = color == Color::White;
	emit whitesTurnChanged(m_whitesTurn);
}

void BoardModel::onSuccessMove(Step step, const Transition&)
{
	
}

void BoardModel::onSubscribed(Board * board)
{
	m_board = board;
}
