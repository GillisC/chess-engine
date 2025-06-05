#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <vector>

#include "pieces/piece.hpp"
#include "pieces/pawn.hpp"
#include "pieces/rook.hpp"
#include "pieces/knight.hpp"
#include "pieces/king.hpp"
#include "pieces/queen.hpp"
#include "pieces/bishop.hpp"

#include "board_position.hpp"

class Piece;


/*
 * The board class is responsible for keeping track of pieces.
 */
class ChessBoard
{
    std::vector<std::vector<std::shared_ptr<Piece>>> _board_data;

public:   
    ChessBoard();
    void move(BoardPosition startPos, BoardPosition endPos);
    void place(BoardPosition targetPos, std::shared_ptr<Piece> piece);
    std::shared_ptr<Piece> at(const BoardPosition& pos);
    bool isPiece(const BoardPosition& pos);
    bool isWhite(const BoardPosition& pos);
    bool isBlack(const BoardPosition& pos);
    bool isInBounds(const BoardPosition& pos);
    
    struct BoardIterator
    {
        ChessBoard* board;
        int pos;

        BoardIterator(ChessBoard* b, int p) : board(b), pos(p) {}
        bool operator!=(const BoardIterator& other) const { return pos != other.pos; }
        void operator++() { pos++; }
        std::shared_ptr<Piece> operator*() { return board->_board_data[pos / 8][pos % 8]; }
    };

    BoardIterator begin() { return BoardIterator(this, 0); }
    BoardIterator end() { return BoardIterator(this, 64); }
};

