# Chess

It's a simple implementation of chess made mainly for run in late 2015.

It supports simple UI mode:
![simple mode](wiki/images/chess-simple-mode.gif)
and so-called "vomit mode":
![vomit mode](wiki/images/chess-vomit-mode.gif)

## Implemented

- turn-by-turn game
- chess pieces with their standard rules
- moves log (w/o saving)

## Not implemented

- check, checkmate, castling, en passant, pawn promotion:
    + it can be more or less easily added using powerful system of constraints
- saving to file, loading from file:
    + application uses two interfaces (`IBoardFiller` and `IBoardObserver`) which could be extended to add this functionality
    + I was intended to use [PGNLib][pgnlib] library to handle this

## Design details

- `Behavior` of each *Piece* consists of several `Constraints` that are combined in one functor for moving (when target position is empty) and one for capturing (when target position is not empty). Please, note that capturing also can be used, for example, for castling.
- `Board` class is not too smart. Real work is done by pieces' `Behavior`s and `IBoardObserver`s.
    + For example, the `BoardModel` implements `IBoardObserver` and plays the role of mediator between game engine and UI.
    + `History` on its turn is intended to save game log and restore it (using the same `IBoardObserver` interface plus `IBoardFiller` for initialization of `Board` state), but it hasn't been implemented yet.

## Target platform

The game was developed using:

- Visual Studio 2013 (msvc2013_x64)
- Qt 5.4
- C++11, QML
- QMake

and successfully tested on:

- Windows 10
- Windows 8.1

[pgnlib]: http://pgnlib.sourceforge.net/
