#pragma once


#include "board.hpp"

class ChessModel
{
    ChessBoard _board;
    Color _currentTurn = Color::WHITE;

public:
    ChessModel();

    // Returns the piece at the provided BoardPosition
    // If there isn't a piece present it will return nullptr
    std::shared_ptr<Piece> atBoardPosition(const BoardPosition& pos);

    // Returns true if the pos contains a chess piece
    bool isPiece(const BoardPosition& pos);

    // Given a board position, returns the possible moves available
    std::vector<BoardPosition> getMoves(const BoardPosition& pos);

    void movePiece(const BoardPosition& from, const BoardPosition& to);
    
    bool isWhitePiece(const BoardPosition& pos);
    bool isBlackPiece(const BoardPosition& pos);

    Color getTurn();
private:
    void toggleTurn();

    std::vector<BoardPosition> getPawnMoves(const BoardPosition& pos);
    std::vector<BoardPosition> getRookMoves(const BoardPosition& pos);
    std::vector<BoardPosition> getKnightMoves(const BoardPosition& pos);
    std::vector<BoardPosition> getBishopMoves(const BoardPosition& pos);
    std::vector<BoardPosition> getKingMoves(const BoardPosition& pos);
    std::vector<BoardPosition> getQueenMoves(const BoardPosition& pos);
}; 
