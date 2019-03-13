#include "Chess/HistoryMove.hpp"

using namespace chess;

HistoryMove::HistoryMove(QObject *parent)
	: QObject{parent}
	, m_isEmpty{true}
	, m_whiteCapture{false}
	, m_blackCapture{false}
{}

void HistoryMove::clear()
{
	m_whitePiece.clear();
	m_whiteFrom.clear();
	m_whiteTo.clear();
	m_whiteCapture = false;

	m_blackPiece.clear();
	m_blackFrom.clear();
	m_blackTo.clear();
	m_blackCapture = false;

	m_isEmpty = true;
	emit isEmptyChanged(m_isEmpty);
}

QString HistoryMove::whitePiece() const
{
	return m_whitePiece;
}

QString HistoryMove::whiteFrom() const
{
	return m_whiteFrom;
}

QString HistoryMove::whiteTo() const
{
	return m_whiteTo;
}

bool HistoryMove::whiteCapture() const
{
	return m_whiteCapture;
}

QString HistoryMove::blackPiece() const
{
	return m_blackPiece;
}

QString HistoryMove::blackFrom() const
{
	return m_blackFrom;
}

QString HistoryMove::blackTo() const
{
	return m_blackTo;
}

bool HistoryMove::blackCapture() const
{
	return m_blackCapture;
}

bool HistoryMove::isEmpty() const
{
	return m_isEmpty;
}

void HistoryMove::setWhitePiece(QString arg)
{
	if (m_whitePiece == arg)
		return;

	m_whitePiece = arg;
	emit whitePieceChanged(arg);
	setIsNotEmpty();
}

void HistoryMove::setWhiteFrom(QString arg)
{
	if (m_whiteFrom == arg)
		return;

	m_whiteFrom = arg;
	emit whiteFromChanged(arg);
	setIsNotEmpty();
}

void HistoryMove::setWhiteTo(QString arg)
{
	if (m_whiteTo == arg)
		return;

	m_whiteTo = arg;
	emit whiteToChanged(arg);
	setIsNotEmpty();
}

void HistoryMove::setWhiteCapture(bool arg)
{
	if (m_whiteCapture == arg)
		return;

	m_whiteCapture = arg;
	emit whiteCaptureChanged(arg);
}

void HistoryMove::setBlackPiece(QString arg)
{
	if (m_blackPiece == arg)
		return;

	m_blackPiece = arg;
	emit blackPieceChanged(arg);
	setIsNotEmpty();
}

void HistoryMove::setBlackFrom(QString arg)
{
	if (m_blackFrom == arg)
		return;

	m_blackFrom = arg;
	emit blackFromChanged(arg);
	setIsNotEmpty();
}

void HistoryMove::setBlackTo(QString arg)
{
	if (m_blackTo == arg)
		return;

	m_blackTo = arg;
	emit blackToChanged(arg);
	setIsNotEmpty();
}

void HistoryMove::setBlackCapture(bool arg)
{
	if (m_blackCapture == arg)
		return;

	m_blackCapture = arg;
	emit blackCaptureChanged(arg);
}

void HistoryMove::setIsNotEmpty()
{
	m_isEmpty = false;
	emit isEmptyChanged(m_isEmpty);
}
