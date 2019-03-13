TEMPLATE = app

QT += core qml quick widgets

TARGET = ChessGame

HEADERS += \
	Chess/Board.hpp \
	Chess/Piece.hpp \
	Chess/PieceImpl.hpp \
	Chess/Position.hpp \
	Chess/Common.hpp \
	Chess/Transition.hpp \
	Chess/Behavior/Behavior.hpp \
	Chess/Behavior/Constraints.hpp \
    Chess/Serialization/PieceSerializer.hpp \
	Chess/BoardModel.hpp \
    Chess/IBoardObserver.hpp \
    Chess/History.hpp \
    Chess/IBoardFiller.hpp \
	Chess/HistoryMove.hpp

SOURCES += main.cpp \
	Chess/Board.cpp \
	Chess/Piece.cpp \
	Chess/Position.cpp \
	Chess/Transition.cpp \
	Chess/BoardModel.cpp \
    Chess/History.cpp \
	Chess/HistoryMove.cpp

RESOURCES += QML/qml.qrc

INCLUDEPATH += $$PWD/../3rdParties

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdParties/pgnlib/release/ -lpgnlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdParties/pgnlib/debug/ -lpgnlib
else:unix: LIBS += -L$$OUT_PWD/../3rdParties/pgnlib/ -lpgnlib

INCLUDEPATH += $$PWD/../3rdParties/pgnlib
DEPENDPATH += $$PWD/../3rdParties/pgnlib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdParties/pgnlib/release/libpgnlib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdParties/pgnlib/debug/libpgnlib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdParties/pgnlib/release/pgnlib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdParties/pgnlib/debug/pgnlib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../3rdParties/pgnlib/libpgnlib.a
