#include "Chess/Board.hpp"

#include "Chess/IBoardObserver.hpp"
#include "Chess/IBoardFiller.hpp"
#include "Chess/Piece.hpp"
#include "Chess/Position.hpp"
#include "Chess/Transition.hpp"

#include <memory>

using namespace chess;

template <int N>
BoardT<N>::BoardT()
	: m_currentTurn{Color::Undefined}
{
	for (int i = 0; i < size(); i++)
		for (int j = 0; j < size(); j++)
			m_table[i][j] = nullptr;
}

template <int N>
int BoardT<N>::size() const
{
	return N;
}

template <int N>
PiecePtr & BoardT<N>::operator[](const Position & pos)
{
	if (!pos.isValid())
		throw std::out_of_range("Position out of range");
	return m_table[pos.row()][pos.column()];
}

template <int N>
const PiecePtr & BoardT<N>::operator[](const Position & pos) const
{
	if (!pos.isValid())
		throw std::out_of_range("Position out of range");
	return m_table[pos.row()][pos.column()];
}

template <int N>
bool BoardT<N>::emptyAt(const Position& pos) const
{
	return !((*this)[pos]);
}

template <int N>
void BoardT<N>::addObserver(std::shared_ptr<IBoardObserver> observer)
{
	observer->onSubscribed(this);
	m_observers.push_back(observer);
}

template <int N>
void BoardT<N>::setFiller(std::shared_ptr<IBoardFiller> filler)
{
	m_filler = filler;
}

template <int N>
void BoardT<N>::onInitialized()
{
	for (auto observer : m_observers)
		observer->onInitialized();
}

template <int N>
void BoardT<N>::onTurnChanged()
{
	for (auto observer : m_observers)
		observer->onTurnChange(m_currentTurn);
}

template <int N>
void BoardT<N>::onSuccessMove(Step step, const Transition & move)
{
	for (auto observer : m_observers)
		observer->onSuccessMove(step, move);
}

template <int N>
Step BoardT<N>::tryMove(const Transition & move) const
{
	auto piece = move.piece();
	if (!piece)
		return Step::Wrong;

	return piece->check(move);
}

template <int N>
Step BoardT<N>::tryMove(const Position & from, const Position & to) const
{
	auto move = createTransition(from, to);
	return tryMove(move);
}

template <int N>
Step BoardT<N>::makeMove(const Position & from, const Position & to)
{
	auto move = createTransition(from, to);
	auto step = tryMove(move);
	switch (step)
	{
	case Step::Move:
	case Step::Capture:
		onSuccessMove(step, move);
		(*this)[to] = (*this)[from];
		(*this)[from] = nullptr;
		toggleTurn();
		onInitialized();
		return step;

	default:
		return Step::Wrong;
	}
}

template <int N>
Transition BoardT<N>::createTransition(const Position & from, const Position & to) const
{
	return Transition{*this, from, to};
}

template <int N>
void BoardT<N>::toggleTurn()
{
	if (m_currentTurn == Color::White)
		m_currentTurn = Color::Black;
	else
		m_currentTurn = Color::White;
	onTurnChanged();
}

template <int N>
void BoardT<N>::reinit()
{
	if (!m_filler)
		return;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			m_table[i][j] = m_filler->createPiece(Position{i,j});

	m_currentTurn = m_filler->getFirstTurn();
	onTurnChanged();

	onInitialized();
}

template <int N>
Color BoardT<N>::whoseTurn() const
{
	return m_currentTurn;
}

// explicit instantiation
template class BoardT<>;
