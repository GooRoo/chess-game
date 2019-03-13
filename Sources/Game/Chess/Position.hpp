#pragma once

namespace chess
{
	class Position
	{
	public:
		Position();
		Position(int row, int column);
		~Position() = default;

		bool isValid() const;

		int row() const;
		void setRow(int r);

		int column() const;
		void setColumn(int col);

	public:
		void stepTo(const Position target);

	public:
		friend bool operator==(const Position & lhs, const Position & rhs);
		friend bool operator!=(const Position & lhs, const Position & rhs);

	private:
		void revalidate();

	private:
		bool m_isValid;

		int m_row;
		int m_column;
	};

}
