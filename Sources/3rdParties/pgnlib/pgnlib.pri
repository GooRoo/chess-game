#-------------------------------------------------
#
# Project created by QtCreator 2015-06-28T20:12:25
#
#-------------------------------------------------

QT -= core gui

TARGET = pgnlib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    PGNCommentText.cpp \
    PGNException.cpp \
    PGNGame.cpp \
    PGNGameCollection.cpp \
    PGNGameResult.cpp \
    PGNMove.cpp \
    PGNMoveList.cpp \
    PGNParser.cpp \
    PGNPiece.cpp \
    PGNPly.cpp \
    PGNPosition.cpp \
    PGNSquare.cpp \
    PGNTag.cpp \
    PGNTagList.cpp

HEADERS += \
    PGNCommentText.h \
    PGNException.h \
    PGNGame.h \
    PGNGameCollection.h \
    PGNGameResult.h \
    PGNMove.h \
    PGNMoveList.h \
    PGNParser.h \
    PGNPiece.h \
    PGNPly.h \
    PGNPosition.h \
    PGNSquare.h \
    PGNTag.h \
    PGNTagList.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
