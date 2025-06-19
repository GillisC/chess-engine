#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <vector>
#include <optional>

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
    std::optional<BoardPosition> _enPassantTarget;

public:   
    ChessBoard();
    void move(BoardPosition startPos, BoardPosition endPos);
    void place(BoardPosition targetPos, std::shared_ptr<Piece> piece);
    void place(PieceType pieceType, Color color, const std::string& pos);
    void place(PieceType pieceType, Color color, const BoardPosition& pos);
    std::shared_ptr<Piece> at(const BoardPosition& pos);
    std::shared_ptr<Piece> at(std::string_view pos);
    bool isPiece(const BoardPosition& pos);
    bool isWhite(const BoardPosition& pos);
    bool isBlack(const BoardPosition& pos);

    // Given a board and the color of a player
    // Returns true if there is a piece at the position and is of the opposite color
    bool isOtherPiece(const BoardPosition& pos, Color color);
    bool isInBounds(const BoardPosition& pos);
    void setEnPassantTarget(const BoardPosition& pos);
    
    std::optional<BoardPosition> getEnPassantTarget();
    bool isEnPassantTarget(const BoardPosition& pos);
    void remove(const BoardPosition& pos);
    void clear();
    static BoardPosition convertNotation(const std::string& pos);
    void print();

    void executeMove(const Move m);
    void undoMove(const Move m);
    void checkEnPassant(const Move m);
    // Returns true if king with the provided color is in check
    bool isKingInCheck(Color color);

    // Overloads
    std::vector<std::shared_ptr<Piece>>& operator[](size_t rank);
    const std::vector<std::shared_ptr<Piece>>& operator[](size_t rank) const;

    
    struct BoardIterator
    {
        ChessBoard* board;
        int pos;

        BoardIterator(ChessBoard* b, int p) : board(b), pos(p) {}
        bool operator==(const BoardIterator& other) const { return pos == other.pos; }
        bool operator!=(const BoardIterator& other) const { return pos != other.pos; }
        BoardIterator& operator++() { pos++; return *this; }
        std::shared_ptr<Piece>& operator*() { return board->_board_data[pos / 8][pos % 8]; }
        BoardPosition position() { return {pos % 8, pos / 8}; }
    };

    BoardIterator begin() { return BoardIterator(this, 0); }
    BoardIterator end() { return BoardIterator(this, 64); }

private:
    std::shared_ptr<Piece> createPiece(PieceType pieceType, Color color);
    BoardPosition findKing(Color kingColor);
};

