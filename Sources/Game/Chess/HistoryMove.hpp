#pragma once

#include <QtCore/QObject>
#include <QtQml/QtQml>

namespace chess
{

	class HistoryMove
		: public QObject
	{
		Q_OBJECT
		Q_PROPERTY(QString whitePiece READ whitePiece WRITE setWhitePiece NOTIFY whitePieceChanged)
		Q_PROPERTY(QString whiteFrom READ whiteFrom WRITE setWhiteFrom NOTIFY whiteFromChanged)
		Q_PROPERTY(QString whiteTo READ whiteTo WRITE setWhiteTo NOTIFY whiteToChanged)
		Q_PROPERTY(bool whiteCapture READ whiteCapture WRITE setWhiteCapture NOTIFY whiteCaptureChanged)
		Q_PROPERTY(QString blackPiece READ blackPiece WRITE setBlackPiece NOTIFY blackPieceChanged)
		Q_PROPERTY(QString blackFrom READ blackFrom WRITE setBlackFrom NOTIFY blackFromChanged)
		Q_PROPERTY(QString blackTo READ blackTo WRITE setBlackTo NOTIFY blackToChanged)
		Q_PROPERTY(bool blackCapture READ blackCapture WRITE setBlackCapture NOTIFY blackCaptureChanged)
		Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)

	public:
		explicit HistoryMove(QObject *parent = nullptr);
		~HistoryMove() = default;

		void clear();

		QString whitePiece() const;
		QString whiteFrom() const;
		QString whiteTo() const;
		bool whiteCapture() const;

		QString blackPiece() const;
		QString blackFrom() const;
		QString blackTo() const;
		bool blackCapture() const;

		bool isEmpty() const;

	public slots:
		void setWhitePiece(QString arg);
		void setWhiteFrom(QString arg);
		void setWhiteTo(QString arg);
		void setWhiteCapture(bool arg);

		void setBlackPiece(QString arg);
		void setBlackFrom(QString arg);
		void setBlackTo(QString arg);
		void setBlackCapture(bool arg);

	signals:
		void whitePieceChanged(QString arg);
		void whiteFromChanged(QString arg);
		void whiteToChanged(QString arg);
		void whiteCaptureChanged(bool arg);

		void blackPieceChanged(QString arg);
		void blackFromChanged(QString arg);
		void blackToChanged(QString arg);
		void blackCaptureChanged(bool arg);

		void isEmptyChanged(bool arg);

	private:
		void setIsNotEmpty();

		QString m_whitePiece;
		QString m_whiteFrom;
		QString m_whiteTo;
		bool m_whiteCapture;
		QString m_blackPiece;
		QString m_blackFrom;
		QString m_blackTo;
		bool m_blackCapture;
		bool m_isEmpty;
	};
}
