#include "chess_model.hpp"

ChessModel::ChessModel() : 
    _owned_board(), _board(_owned_board) {}

ChessModel::ChessModel(ChessBoard& board) :
    _board(board) {}

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
    if (!_board.isPiece(pos))
    {
        return {};
    }
    std::vector<Move> possibleMoves = atBoardPosition(pos)->getValidMoves(_board, pos);

    std::vector<Move> validMoves = {};
    auto current = _currentTurn;

    // Filter out moves which lead to the king in check
    for (auto& move : possibleMoves)
    {
        _board.executeMove(move);
        if (!_board.isKingInCheck(current)) validMoves.push_back(move);
        _board.undoMove(move);
    }
    return validMoves;
}

void ChessModel::executeMove(const Move m)
{
    _board.executeMove(m);
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



