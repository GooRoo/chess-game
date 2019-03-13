#pragma once

#include <Chess/Common.hpp>
#include <Chess/Piece.hpp>
#include <Chess/Position.hpp>
#include <Chess/Transition.hpp>

namespace chess
{
	namespace constraints
	{
		struct Direction
		{
			bool pathIsClear(const Transition & move) const
			{
				auto isClear = true;
				auto pos = move.from();
				pos.stepTo(move.to());
				for (; pos != move.to(); pos.stepTo(move.to()))
				{
					if (!move.board().emptyAt(pos))
					{
						isClear = false;
						break;
					}
				}
				return isClear;
			}

			chess::Direction direction(const Transition & move) const
			{
				auto difference = move.to().row() - move.from().row();
				if (difference > 0)
					return chess::Direction::Downward;
				else if (difference < 0)
					return chess::Direction::Upward;
				else
					return chess::Direction::NoMove;
			}
		};
		
		struct Horizontal : Direction
		{
			bool operator()(const Transition & move) const
			{
				return move.verticalLength() == 0
					&& move.horizontalLength() != 0
					&& pathIsClear(move);
			}
		};

		struct Vertical : Direction
		{
			bool operator()(const Transition & move) const
			{
				return move.horizontalLength() == 0
					&& move.verticalLength() != 0
					&& pathIsClear(move);

			}
		};

		struct Diagonal : Direction
		{
			bool operator()(const Transition & move) const
			{
				return move.horizontalLength() != 0
					&& move.verticalLength() != 0
					&& move.horizontalLength() == move.verticalLength()
					&& pathIsClear(move);
			}
		};

		template <int N>
		struct Length
		{
			bool operator()(const Transition & move) const
			{
				return (move.horizontalLength() == 0 && move.verticalLength() == N)
					|| (move.horizontalLength() == N && move.verticalLength() == 0)
					|| (move.horizontalLength() == N && move.verticalLength() == N);
			}
		};

		struct PawnLongStep
		{
			bool operator()(const Transition & move) const
			{
				switch (move.pieceColor())
				{
				case Color::White: 
					return move.from().row() == 6
						&& move.to().row() == 4;

				case Color::Black:
					return move.from().row() == 1 
						&& move.to().row() == 3;;

				default:
					return false;
				}
			}
		};

		struct Knight
		{
			bool operator()(const Transition & move) const
			{
				return (move.horizontalLength() == 1 && move.verticalLength() == 2)
					|| (move.horizontalLength() == 2 && move.verticalLength() == 1);
			}
		};

		struct Forward : Direction
		{
			bool operator()(const Transition & move) const
			{
				switch (move.pieceColor())
				{
				case Color::White:
					return direction(move) == chess::Direction::Upward;

				case Color::Black:
					return direction(move) == chess::Direction::Downward;

				default:
					return false;
				}
			}
		};

		struct AnotherColor
		{
			bool operator()(const Transition & move) const
			{
				return (move.pieceColor() == Color::Undefined)
					|| (move.targetColor() == Color::Undefined)
					|| (move.pieceColor() != move.targetColor());
			}
		};

		struct SameColor : AnotherColor
		{
			bool operator()(const Transition & move) const
			{
				return !AnotherColor::operator()(move);
			}
		};

		struct Castling : SameColor
		{
			bool operator()(const Transition & move) const
			{
				// TODO: check whether castling is possible
				return move.target()->type() == PieceType::Rook && SameColor::operator()(move);
			}
		};

		struct MyTurn
		{
			bool operator()(const Transition & move) const
			{
				return move.piece()->color() == move.board().whoseTurn();
			}
		};

		struct NotUnderAttack
		{
			bool operator()(const Transition &) const
			{
				return true;
			}
		};

		template <typename ...Ts>
		struct Any
		{
			bool operator()(const Transition &) const 
			{
				return false;
			}
		};

		template <typename T, typename ...Ts>
		struct Any<T, Ts...>
		{
			bool operator()(const Transition & move) const
			{
				return left(move) || right(move);
			}

		private:
			T left;
			Any<Ts...> right;
		};

		template <typename ...Ts>
		struct All
		{
			bool operator()(const Transition &) const
			{
				return true;
			}
		};

		template <typename T, typename ...Ts>
		struct All<T, Ts...>
		{
			bool operator()(const Transition & move) const
			{
				return left(move) && right(move);
			}

		private:
			T left;
			All<Ts...> right;
		};
	}
}
