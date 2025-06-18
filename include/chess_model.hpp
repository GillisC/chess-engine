#pragma once

#include <map>

#include "board.hpp"
#include "move.hpp"
#include "human_controller.hpp"
#include "engine_controller.hpp"

class ChessModel
{
    ChessBoard _owned_board;
    ChessBoard& _board;
    std::map<Color, std::unique_ptr<Controller>> controllers;
    Color _currentTurn = Color::White;
    
public:
    ChessModel();
    ChessModel(ChessBoard& board);

    // Returns the piece at the provided BoardPosition
    // If there isn't a piece present it will return nullptr
    std::shared_ptr<Piece> atBoardPosition(const BoardPosition& pos);

    // Returns true if the pos contains a chess piece
    bool isPiece(const BoardPosition& pos);

    // Given a board position, returns the possible moves available
    std::vector<Move> getMoves(const BoardPosition& pos);
    std::vector<Move> getAllLegalMoves(Color color);

    void executeMove(const Move m);
    void startTurn();
 
    void movePiece(const BoardPosition& from, const BoardPosition& to);
    
    bool isWhitePiece(const BoardPosition& pos);
    bool isBlackPiece(const BoardPosition& pos);

    Color getTurn();

    // FEN
    // Exports the current gamestate in the FEN (Forsyth-Edwards Notation) format
    std::string getFEN();

    // Sets the model game state based on the provided FEN string
    void loadFEN(const std::string& fenString);

private:
    void toggleTurn();
    char pieceToSymbol(std::shared_ptr<Piece> p);
    std::shared_ptr<Piece> symbolToPiece(char sym);

}; 
