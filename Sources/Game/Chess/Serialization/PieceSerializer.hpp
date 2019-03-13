#pragma once

#include <cctype>

#include "Chess/Common.hpp"

namespace chess
{

	template <PieceType T>
	struct GenericPieceSerializer;

	template <>
	struct GenericPieceSerializer<PieceType::King>
	{
		char letter() const
		{
			return 'k';
		}
	};

	template <>
	struct GenericPieceSerializer<PieceType::Queen>
	{
		char letter() const
		{
			return 'q';
		}
	};

	template <>
	struct GenericPieceSerializer<PieceType::Rook>
	{
		char letter() const
		{
			return 'r';
		}
	};

	template <>
	struct GenericPieceSerializer<PieceType::Bishop>
	{
		char letter() const
		{
			return 'b';
		}
	};

	template <>
	struct GenericPieceSerializer<PieceType::Knight>
	{
		char letter() const
		{
			return 'n';
		}
	};

	template <>
	struct GenericPieceSerializer<PieceType::Pawn>
	{
		char letter() const
		{
			return 'p';
		}
	};

	template <PieceType T, Color C>
	struct PieceSerializer;

	template <PieceType T>
	struct PieceSerializer<T, Color::Black> : GenericPieceSerializer<T>
	{};

	template <PieceType T>
	struct PieceSerializer<T, Color::White> : GenericPieceSerializer<T>
	{
		char letter() const
		{
			return std::toupper(GenericPieceSerializer<T>::letter());
		}
	};
}
