#pragma once

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QPair>

#include "Chess/IBoardFiller.hpp"
#include "Chess/IBoardObserver.hpp"
#include "Chess/HistoryMove.hpp"

#include "pgnlib/PGNGameCollection.h"

namespace pgn
{
	class Game;
}

namespace chess
{
	class Piece;
	class Position;

	class History
		: public QObject
		, public IBoardObserver
		, public IBoardFiller
	{
		Q_OBJECT
		Q_PROPERTY(chess::HistoryMove* lastMove READ lastMove NOTIFY lastMoveChanged)
	public:
		History(QObject *parent = nullptr);
		virtual ~History();

	signals:
		void lastMoveChanged(HistoryMove* moves);

	public slots:
		void onNewGame();

	public:
		HistoryMove * lastMove() const;

		// IBoardObserver interface
		void onSubscribed(Board * board) override;
		void onSuccessMove(Step step, const Transition & move) override;

		// IBoardFiller interface
		std::shared_ptr<Piece> createPiece(const Position & pos) const override;
		Color getFirstTurn() const override;

	private:
		// TODO: use it somehow
//		pgn::Game * m_currentGame;
//		pgn::GameCollection m_games;

		Board * m_board;
		HistoryMove * m_halfMove;
	};
}
