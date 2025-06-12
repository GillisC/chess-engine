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



std::vector<Move> ChessModel::getMoves(const BoardPosition& pos)
{
    std::vector<Move> validMoves = {};

    if (!isPiece(pos)) return validMoves;
    
    return atBoardPosition(pos)->getValidMoves(_board, pos);
}

void ChessModel::executeMove(const Move m)
{
    Color c = _board.at(m.from)->getColor();
    _board.at(m.from)->incrementMoved();
    _board.move(m.from, m.to);

    // Move the secondary piece if provided
    if (m.secondaryFrom.has_value() && m.secondaryTo.has_value())
    {
        _board.at(m.secondaryFrom.value())->incrementMoved();
        _board.move(m.secondaryFrom.value(), m.secondaryTo.value());
    }

    // Promote if provided
    if (m.promotion.has_value())
    {
        _board.place(m.promotion.value(), c, m.to);
    }

    toggleTurn();
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



