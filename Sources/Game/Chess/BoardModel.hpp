#pragma once

#include <QtCore/QObject>
#include <QtCore/QStringList>

#include "Chess/IBoardObserver.hpp"

namespace chess
{
	class BoardModel
		: public QObject
		, public IBoardObserver
	{
		Q_OBJECT
		Q_PROPERTY(QStringList pieces READ pieces NOTIFY piecesChanged)
		Q_PROPERTY(bool whitesTurn READ whitesTurn NOTIFY whitesTurnChanged)
	public:
		explicit BoardModel(QObject *parent = nullptr);
		virtual ~BoardModel();

		QStringList pieces() const;
		bool whitesTurn() const;

	signals:
		void newGameRequested();
		void piecesChanged(QStringList arg);
		void whitesTurnChanged(bool arg);

	public slots:
		void newGame();
		bool tryMove(int x1, int y1, int x2, int y2) const;
		bool makeMove(int x1, int y1, int x2, int y2);

		// IBoardObserver interface
	public:
		void onSubscribed(Board * board) override;
		void onInitialized() override;
		void onTurnChange(Color color) override;
		void onSuccessMove(Step step, const Transition & move) override;

	private:
		Board * m_board;
		QStringList m_pieces;
		bool m_whitesTurn;
	};
}
