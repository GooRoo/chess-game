#pragma once

#include "Chess/Common.hpp"
#include "Chess/Piece.hpp"
#include "Chess/Behavior/Behavior.hpp"
#include "Chess/Serialization/PieceSerializer.hpp"

namespace chess
{
	template <PieceType T, Color C>
	class PieceImpl 
		: public Piece
		, private BehaviorChecker<T>
		, private PieceSerializer<T, C>
	{
	public:
		PieceImpl(const Board * board);
		virtual ~PieceImpl() = default;

		Step check(const Transition &move) const override;
		char letter() const override;
		Color color() const override;
		PieceType type() const override;

	private:
		bool checkMove(const Transition& move) const;
		bool checkCapture(const Transition& move) const;
	};

	template <PieceType T, Color C>
	PieceImpl<T, C>::PieceImpl(const Board *board)
		: Piece{board}
	{}

	template <PieceType T, Color C>
	Step PieceImpl<T, C>::check(const Transition &move) const
	{
		if (!move.target())
			return checkMove(move)? Step::Move : Step::Wrong;
		else
			return checkCapture(move)? Step::Capture : Step::Wrong;
	}

	template <PieceType T, Color C>
	bool PieceImpl<T, C>::checkMove(const Transition& move) const
	{
		return BehaviorChecker<T>::checkMove(move);
	}

	template <PieceType T, Color C>
	bool PieceImpl<T, C>::checkCapture(const Transition& move) const
	{
		return BehaviorChecker<T>::checkCapture(move);
	}

	template <PieceType T, Color C>
	char PieceImpl<T, C>::letter() const
	{
		return PieceSerializer<T, C>::letter();
	}

	template <PieceType T, Color C>
	Color PieceImpl<T, C>::color() const
	{
		return C;
	}

	template <PieceType T, Color C>
	PieceType PieceImpl<T, C>::type() const
	{
		return T;
	}

	template <PieceType T, Color C, typename ...Args>
	std::shared_ptr<Piece> make_piece(Args... args)
	{
		return std::make_shared<PieceImpl<T, C>>(args...);
	}
}
