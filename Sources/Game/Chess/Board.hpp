#pragma once

#include <array>
#include <memory>
#include <list>

#include "Chess/Common.hpp"

namespace chess
{
	class IBoardObserver;
	class IBoardFiller;
	class Position;
	class Piece;
	class Transition;

	using PiecePtr = std::shared_ptr<Piece>;

	template <int N = MaxBoardSize>
	class BoardT
	{
	public:
		BoardT();
		~BoardT() = default;

		//constexpr
		int size() const;

		//Piece * begin();
		//Piece * end();

		PiecePtr & operator[](const Position & pos);
		const PiecePtr & operator[](const Position & pos) const;

		bool emptyAt(const Position & pos) const;

		Step tryMove(const Position & from, const Position & to) const;
		Step makeMove(const Position & from, const Position & to);

		void addObserver(std::shared_ptr<IBoardObserver> observer);
		void setFiller(std::shared_ptr<IBoardFiller> filler);

		void reinit();

		Color whoseTurn() const;

	private:
		void onInitialized();
		void onTurnChanged();
		void onSuccessMove(Step step, const Transition & move);
		
		Step tryMove(const Transition & move) const;
		Transition createTransition(const Position & from, const Position & to) const;
		void toggleTurn();

	private:
		using PieceTable = std::array<std::array<PiecePtr, N>, N>; // Piece*[N][N]
		PieceTable m_table;

		using Observers = std::list<std::shared_ptr<IBoardObserver>>;
		Observers m_observers;

		std::shared_ptr<IBoardFiller> m_filler;

		Color m_currentTurn;
	};

	using Board = BoardT<>;
}
