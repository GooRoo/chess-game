#include "Chess/History.hpp"

#include "Chess/Piece.hpp"
#include "Chess/PieceImpl.hpp"
#include "Chess/Position.hpp"

#include "pgnlib/PGNGame.h"
#include "pgnlib/PGNGameCollection.h"

using namespace chess;

static const char defaultState[] = {
	'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
	'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
	'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'
};

namespace
{
	char rowToLetter(int row)
	{
		static const char eight = '8';
		return eight - row;
	}

	char columnToLetter(int column)
	{
		return 'a' + column;
	}
}

History::History(QObject * parent)
	: QObject{parent}
//	, m_currentGame{nullptr}
	, m_board{nullptr}
	, m_halfMove{nullptr}
{

}

History::~History()
{
	delete m_halfMove;
	m_halfMove = nullptr;
}

void History::onNewGame()
{
//	if (m_currentGame)
//	{
//		m_games.push_back(*m_currentGame);
//		delete m_currentGame;
//	}

//	m_currentGame = new pgn::Game;

	m_board->reinit();
	if (m_halfMove)
	{
		m_halfMove->clear();
		emit lastMoveChanged(m_halfMove);
	}
}

HistoryMove * History::lastMove() const
{
	return m_halfMove;
}

std::shared_ptr<Piece> History::createPiece(const Position & pos) const
{
	auto index = pos.row() * 8 + pos.column();
	switch (defaultState[index])
	{
	case 'r':
		return make_piece<PieceType::Rook, Color::Black>(m_board);

	case 'n':
		return make_piece<PieceType::Knight, Color::Black>(m_board);

	case 'b':
		return make_piece<PieceType::Bishop, Color::Black>(m_board);

	case 'q':
		return make_piece<PieceType::Queen, Color::Black>(m_board);

	case 'k':
		return make_piece<PieceType::King, Color::Black>(m_board);

	case 'p':
		return make_piece<PieceType::Pawn, Color::Black>(m_board);

	case 'R':
		return make_piece<PieceType::Rook, Color::White>(m_board);

	case 'N':
		return make_piece<PieceType::Knight, Color::White>(m_board);

	case 'B':
		return make_piece<PieceType::Bishop, Color::White>(m_board);

	case 'Q':
		return make_piece<PieceType::Queen, Color::White>(m_board);

	case 'K':
		return make_piece<PieceType::King, Color::White>(m_board);

	case 'P':
		return make_piece<PieceType::Pawn, Color::White>(m_board);

	default:
		return nullptr;
	}
}

Color History::getFirstTurn() const
{
	return Color::White;
}

void History::onSubscribed(Board * board)
{
	m_board = board;
}

void History::onSuccessMove(Step step, const Transition& move)
{
	if (!m_halfMove)
		m_halfMove = new HistoryMove;

	QString letter = move.piece()->letter();
	QString coord{"%1%2"};
	QString from = coord
		.arg(rowToLetter(move.from().row()))
		.arg(columnToLetter(move.from().column()))
	;
	QString to = coord
		.arg(rowToLetter(move.to().row()))
		.arg(columnToLetter(move.to().column()))
	;
	bool capture = step == Step::Capture;

	if (move.board().whoseTurn() == Color::White)
	{
		m_halfMove->setWhitePiece(letter);
		m_halfMove->setWhiteFrom(from);
		m_halfMove->setWhiteTo(to);
		m_halfMove->setWhiteCapture(capture);
	}
	else
	{
		m_halfMove->setBlackPiece(letter);
		m_halfMove->setBlackFrom(from);
		m_halfMove->setBlackTo(to);
		m_halfMove->setBlackCapture(capture);

		emit lastMoveChanged(m_halfMove);
	}
}
