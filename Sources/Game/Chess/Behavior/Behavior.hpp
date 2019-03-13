#pragma once

#include "Chess/Common.hpp"
#include "Chess/Behavior/Constraints.hpp"

namespace chess
{
	namespace cc = chess::constraints;

	template <PieceType T>
	struct Behavior;

	template <>
	struct Behavior<PieceType::Pawn>
	{
		using move_checker_t = cc::All<
			cc::MyTurn,
			cc::Vertical, 
			cc::Any<
				cc::Length<1>, 
				cc::PawnLongStep
			>,
			cc::Forward
		>;
		using capture_checker_t = cc::All<
			cc::MyTurn,
			cc::Diagonal,
			cc::Length<1>, 
			cc::Forward,
			cc::AnotherColor
		>;
	};

	template <>
	struct Behavior<PieceType::Knight>
	{
		using move_checker_t = cc::All<cc::MyTurn, cc::Knight>;
		using capture_checker_t = cc::All<move_checker_t, cc::AnotherColor>;
	};

	template <>
	struct Behavior<PieceType::Bishop>
	{
		using move_checker_t = cc::All<cc::MyTurn, cc::Diagonal>;
		using capture_checker_t = cc::All<move_checker_t, cc::AnotherColor>;
	};

	template <>
	struct Behavior<PieceType::Rook>
	{
		using move_checker_t = cc::All<
			cc::MyTurn,
			cc::Any<
				cc::Horizontal, 
				cc::Vertical
			>
		>;
		using capture_checker_t = cc::All<move_checker_t, cc::AnotherColor>;
	};

	template <>
	struct Behavior<PieceType::Queen>
	{
		using move_checker_t = cc::All<
			cc::MyTurn,
			cc::Any<
				cc::Horizontal, 
				cc::Vertical, 
				cc::Diagonal
			>
		>;
		using capture_checker_t = cc::All<move_checker_t, cc::AnotherColor>;
	};

	template <>
	struct Behavior<PieceType::King>
	{
		using move_checker_t = cc::All<
			cc::MyTurn,
			cc::Any<
				cc::Horizontal, 
				cc::Vertical, 
				cc::Diagonal
			>, 
			cc::Length<1>, 
			cc::NotUnderAttack
		>;
		using capture_checker_t = cc::All<move_checker_t, cc::Any<cc::AnotherColor, cc::Castling>>;
	};

	template <PieceType T>
	struct BehaviorChecker : Behavior<T>
	{
		bool checkMove(const Transition& move) const
		{
			return moveChecker(move);
		}

		bool checkCapture(const Transition& move) const
		{
			return captureChecker(move);
		}

	private:
		using move_checker_t = typename BehaviorChecker<T>::move_checker_t;
		using capture_checker_t = typename BehaviorChecker<T>::capture_checker_t;
		move_checker_t moveChecker;
		capture_checker_t captureChecker;
	};
}
