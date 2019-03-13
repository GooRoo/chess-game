#pragma once

#include <memory>
#include "Common.hpp"

namespace chess
{
	class Piece;
	class Position;

	class IBoardFiller
	{
	public:
		virtual ~IBoardFiller() = default;

		virtual std::shared_ptr<Piece> createPiece(const Position & pos) const = 0;
		virtual Color getFirstTurn() const = 0;
	};
}
