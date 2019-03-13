//
// Copyright (C) 2002 Andrea Vinzoni <vinzoni@users.sourceforge.net>
//
//     This file is part of pgnlib.
//
//     pgnlib is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 2 of the License, or
//     (at your option) any later version.
//
//     pgnlib is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//     See the GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with pgnlib; if not, write to the Free Software Foundation,
//     Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include <cstdio>
#include <sstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <cstdlib>
#include <PGNPly.h>
#include <PGNCommentText.h>
#include <PGNMoveList.h>
#include <PGNException.h>
#include <PGNParser.h>

#include <iostream>

namespace pgn
{
    struct PlyData
    {
        std::string text;
        char fromsquare_letter;
        char fromsquare_number;
        pgn::CommentText *comment;
        std::vector<pgn::MoveList *>variation;

        PlyData()
        :fromsquare_letter(0),fromsquare_number(0),comment(0)
        {}

        //
        // complete_from = true: you ask for the full square text of the ply
        // (i.e. 'f3' if Nf3-e5 has been played)
        // complete_from = false: you ask for what you need to write down the
        // ply. So you can get '' (ply=Ne5) or 'f' (Nfe5) or '3' (N3e5).
        //
        void squares(std::string &from, std::string &to, bool complete_from);

        bool promotion() const
        {
            return text.find("=") != std::string::npos;
        }

        Piece fromPiece() const;
        Piece toPiece() const;
    };

    void PlyData::squares(std::string &from, std::string &to, bool complete_from)
    {
        char x_coord = 0;
        char y_coord = 0;
        char e_coord = 0;
        for (unsigned int i=0; i<text.size(); ++i)
        {
            if ((text[i] >= 'a' && text[i] <= 'h') ||
                (text[i] >= '1' && text[i] <= '8'))
            {
                if (!e_coord)
                    e_coord = text[i];
                else if (!x_coord)
                    x_coord = text[i];
                else
                    y_coord = text[i];
            }
        }
        if (!y_coord)
        {
            y_coord = x_coord;
            x_coord = e_coord;
            e_coord = 0;
        }
        std::stringstream ss;
        // I am the public Ply::fromSquare() method: I need the full info
        if ((complete_from == true) && fromsquare_letter && fromsquare_number)
        {
            ss << fromsquare_letter << fromsquare_number;
        }
        // I am the operator << (): I need the minimum info to disambiguate the move
        else if (e_coord)
        {
            ss << e_coord;
        }

        from = ss.str();
        ss.str("");
        ss <<  x_coord << y_coord;
        to = ss.str();
    }

    Piece PlyData::fromPiece() const
    {
        switch (text[0])
        {
            case 'R':
                return pgn::Piece::Rook();
            case 'K':
                return pgn::Piece::King();
            case 'Q':
                return pgn::Piece::Queen();
            case 'B':
                return pgn::Piece::Bishop();
            case 'N':
                return pgn::Piece::Knight();
            default:
                return pgn::Piece::Pawn();
        }
    }

    Piece PlyData::toPiece() const
    {
        if (promotion())
        {
            size_t pos = text.find("=");
            return pgn::Piece(text[pos+1]);
        }
        else
            return fromPiece();
    }

};

pgn::Ply::Ply(const pgn::Ply& src)
{
    hdata = new PlyData;

    hdata->text = src.hdata->text;
    hdata->fromsquare_letter = src.hdata->fromsquare_letter;
    hdata->fromsquare_number = src.hdata->fromsquare_number;
    if (src.hdata->comment)
        hdata->comment = new pgn::CommentText(*(src.hdata->comment));
    else
        hdata->comment = 0;
    for (unsigned int i=0; i<src.hdata->variation.size(); ++i)
        hdata->variation.push_back(new pgn::MoveList(*(src.hdata->variation[i])));

//	std::cout << "new PlyData " << sizeof(*hdata) << std::endl;
}

pgn::Ply::Ply()
{
    hdata = new PlyData;
    hdata->comment = 0;
}

//pgn::Ply::Ply(const std::string& ply_text, const Square &from)
pgn::Ply::Ply(const std::string& ply_text)
{
    hdata = new PlyData;
//	std::cout << "new PlyData " << sizeof(*hdata) << std::endl;
    hdata->text = ply_text;
//	hdata->fromsquare_letter = from.col();
//	hdata->fromsquare_number = from.row();
    hdata->fromsquare_letter = 0;
    hdata->fromsquare_number = 0;
    hdata->comment = 0;
}

pgn::Ply::~Ply()
{
    unbindVariations();
    delete hdata->comment; hdata->comment=0;
    delete hdata; hdata=0;
}

std::string pgn::Ply::str() const
{
    return hdata->text;
}

bool pgn::Ply::valid() const
{
    return isShortCastle() || isLongCastle() || toSquare().valid();
}

pgn::Ply& pgn::Ply::operator = (const pgn::Ply& src)
{
    if (&src == this)
        return(*this);

    hdata->text = src.hdata->text;
    hdata->fromsquare_letter = src.hdata->fromsquare_letter;
    hdata->fromsquare_number = src.hdata->fromsquare_number;

    if (src.hdata->comment)
    {
        delete hdata->comment; hdata->comment=0;
        hdata->comment = new pgn::CommentText(*(src.hdata->comment));
    }
    else
        hdata->comment = 0;

    unbindVariations();

    for (unsigned int i=0; i<src.hdata->variation.size(); ++i)
        hdata->variation.push_back(new pgn::MoveList(*(src.hdata->variation[i])));

    return *this;
}

//
// I choose not to consider fromsquare_letter and fromsquare_number to test for equality.
// To me "Nf6" is equal to "Nf6", in a pgn sense, regardless from where the knight come from.
//
bool pgn::Ply::operator == (const pgn::Ply& src) const
{
    if (hdata->text != src.hdata->text)
        return false;

    if ((hdata->comment != 0) && (src.hdata->comment != 0) &&
            *(hdata->comment) != *(src.hdata->comment))
        return false;

    if (((hdata->comment == 0) && (src.hdata->comment != 0)) ||
        ((hdata->comment != 0) && (src.hdata->comment == 0)))
        return false;

    return true;
}

std::ostream& pgn::operator << ( std::ostream& os, const pgn::Ply& src )
{
    if (!src.valid())
    {
        return os;
    }

    if (src.isLongCastle())
    {
        os << "O-O-O";
        if (src.isCheckMate())
            os << "#";
        else if (src.isCheck())
            os << "+";
    }
    else if (src.isShortCastle())
    {
        os << "O-O";
        if (src.isCheckMate())
            os << "#";
        else if (src.isCheck())
            os << "+";
    }
    else
    {
        os << src.piece();
        std::string from, to;
        src.hdata->squares(from, to, false);
        os << pgn::Square(from[0], from[1]);
//		os << src.fromSquare();
        if (src.isCapture())
            os << "x";
        os << src.toSquare();
        if (src.promotion())
            os << "=" << src.promoted();
        if (src.isCheckMate())
            os << "#";
        else if (src.isCheck())
            os << "+";
    }

    if (src.glyphValue() >= 0)
    {
        os << "$" << src.glyphValue();
    }

    if (src.hdata->comment)
        os << *(src.hdata->comment);

    for (unsigned int i=0; i<src.hdata->variation.size(); ++i)
        os << "(" << *(src.hdata->variation[i]) << ") ";

    return os;
}

std::istream& pgn::operator >> ( std::istream& is, pgn::Ply& src )
{
    std::string str;
    std::copy(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>(), std::inserter(str, str.end()));
    pgn::Parser parser;
    std::string::const_iterator itr1 = str.begin();
    std::string::const_iterator itr2 = str.end();
    parser.getPly(itr1, itr2, src);
    return is;
}

bool pgn::Ply::operator != (const pgn::Ply& src) const
{
    return !(src == *this);
}

bool pgn::Ply::isLongCastle() const
{
    if (hdata->text.find("O-O-O") != std::string::npos)
        return true;
    else
        return false;
}

bool pgn::Ply::isShortCastle() const
{
    if ((hdata->text.find("O-O") != std::string::npos) && !isLongCastle())
        return true;
    else
        return false;
}

bool pgn::Ply::isCapture() const
{
    if (hdata->text.find("x") != std::string::npos)
        return true;
    else
        return false;
}

bool pgn::Ply::isCheck() const
{
    if (hdata->text.find("+") != std::string::npos)
        return true;
    else
        return false;
}

bool pgn::Ply::isCheckMate() const
{
    if (hdata->text.find("#") != std::string::npos)
        return true;
    else
        return false;
}

pgn::Square pgn::Ply::fromSquare() const
{
    std::string from;
    std::string to;
    hdata->squares(from, to, true);

    if ((from.size() == 1) && (from[0] >= '1') && (from[0] <= '8'))
        return pgn::Square(0, from[0], hdata->fromPiece());
    else if ((from.size() == 1) && (from[0] >= 'a') && (from[0] <= 'h'))
        return pgn::Square(from[0], 0, hdata->fromPiece());
    else
        return pgn::Square(from[0], from[1], hdata->fromPiece());
}

pgn::Square pgn::Ply::toSquare() const
{
    std::string from;
    std::string to;
    hdata->squares(from, to, true);
    return pgn::Square(to[0], to[1], hdata->toPiece());
}

pgn::Piece pgn::Ply::piece() const
{
    return fromSquare().piece();
}

bool pgn::Ply::promotion() const
{
    return hdata->promotion();
}

pgn::Piece pgn::Ply::promoted() const
{
    if (hdata->promotion())
        return toSquare().piece();
    else
        return pgn::Piece::Null();
}

void pgn::Ply::setGlyphValue(int glyphval)
{
    size_t pos = hdata->text.find("$");

    if (pos != std::string::npos)
        hdata->text = hdata->text.substr(0, pos);

    std::stringstream ss;
    ss << hdata->text << "$" << glyphval;
    hdata->text = ss.str();
}

void pgn::Ply::setFromSquare(const Square &s)
{
    hdata->fromsquare_letter = s.col();
    hdata->fromsquare_number = s.row();
}

void pgn::Ply::setToSquare(const Square &s)
{
    // For the time being the 'to' coordinates are coded directly into hdata->text (that's going to change soon)
    int colpos = hdata->text.find_last_of("abcdefgh");
    int rowpos = colpos + 1;
    hdata->text[colpos] = s.col();
    hdata->text[rowpos] = s.row();
}

void pgn::Ply::setPiece(const Piece &p)
{
    if ((p.letter() != 'P')  && // 'P' means pawn
        (p.letter() != '0')) // '0' means no piece
        hdata->text[0] = p.letter();
}

int pgn::Ply::glyphValue() const
{
    size_t pos = hdata->text.find("$");

    if (pos == std::string::npos)
        return -1;

    return atoi(hdata->text.substr(pos+1).c_str());
}

void pgn::Ply::bindComment(const CommentText &comment)
{
    delete hdata->comment;
    hdata->comment = new pgn::CommentText(comment);
}

void pgn::Ply::unbindComment()
{
    delete hdata->comment;
    hdata->comment = 0;
}

void pgn::Ply::bindVariation(const MoveList &variation)
{
    hdata->variation.push_back(new pgn::MoveList(variation));
}

void pgn::Ply::unbindVariations()
{
    for (unsigned int i=0; i<hdata->variation.size(); ++i)
      delete hdata->variation[i];
    hdata->variation.clear();
}

