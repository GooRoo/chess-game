#include <iostream>
#include <memory>

#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtWidgets/QApplication>

#include "Chess/Board.hpp"
#include "Chess/BoardModel.hpp"
#include "Chess/History.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	chess::Board b;

	auto bm = std::make_shared<chess::BoardModel>();
	b.addObserver(bm);

	auto h = std::make_shared<chess::History>();
	b.addObserver(h);
	b.setFiller(h);

	QObject::connect(bm.get(), SIGNAL(newGameRequested()), h.get(), SLOT(onNewGame()));

	qmlRegisterType<chess::HistoryMove>();

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("boardModel", bm.get());
	engine.rootContext()->setContextProperty("history", h.get());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
