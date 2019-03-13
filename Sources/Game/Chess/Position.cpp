#include "Chess/Position.hpp"

#include "Chess/Common.hpp"

namespace
{
	inline bool validate(int n)
	{
		return n >= 0 && n < chess::MaxBoardSize;
	}
}

using namespace chess;

Position::Position()
	: Position{-1, -1}
{}

Position::Position(int r, int c)
	: m_isValid{validate(r) && validate(c)}
	, m_row{r}
	, m_column{c}
{}

bool Position::isValid() const
{
	return m_isValid;
}

int Position::row() const
{
	return m_row;
}

void Position::setRow(int r)
{
	m_row = r;
	revalidate();
}

int Position::column() const
{
	return m_column;
}

void Position::setColumn(int col)
{
	m_column = col;
	revalidate();
}

void Position::stepTo(const Position target)
{
	if (m_row < target.m_row)
		++m_row;
	else if (m_row > target.m_row)
		--m_row;

	if (m_column < target.m_column)
		++m_column;
	else if (m_column > target.m_column)
		--m_column;
}

void Position::revalidate()
{
	m_isValid = validate(m_row) && validate(m_column);
}

bool chess::operator==(const chess::Position & lhs, const chess::Position & rhs)
{
	return (lhs.m_isValid == rhs.m_isValid)
		&& (lhs.m_row == rhs.m_row)
		&& (lhs.m_column == rhs.m_column);
}

bool chess::operator!=(const chess::Position & lhs, const chess::Position & rhs)
{
	return !(lhs == rhs);
}
