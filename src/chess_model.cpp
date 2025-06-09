#include "chess_model.hpp"

ChessModel::ChessModel() : 
    _board()
    {}


std::shared_ptr<Piece> ChessModel::atBoardPosition(const BoardPosition& pos)
{
    return _board.at(pos);
}


bool ChessModel::isPiece(const BoardPosition& pos)
{
    return _board.at(pos) != nullptr;
}



std::vector<BoardPosition> ChessModel::getMoves(const BoardPosition& pos)
{
    std::vector<BoardPosition> validMoves = {};

    if (!isPiece(pos)) return validMoves;
    
    return atBoardPosition(pos)->getValidMoves(_board, pos);
}


void ChessModel::movePiece(const BoardPosition& from, const BoardPosition& to)
{
    _board.move(from, to);
    toggleTurn();
}


Color ChessModel::getTurn()
{
    return _currentTurn;
}

// ========= Private =============

void ChessModel::toggleTurn()
{
    _currentTurn = (_currentTurn == Color::White) ? Color::Black : Color::White;
}



