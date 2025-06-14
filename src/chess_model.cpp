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

    checkEnPassant(m);

    // Move the secondary piece if provided
    if (m.secondaryFrom.has_value() && m.secondaryTo.has_value())
    {
        _board.at(m.secondaryFrom.value())->incrementMoved();
        _board.move(m.secondaryFrom.value(), m.secondaryTo.value());
    }
    // En passant execution remove the piece that been en passant'ed
    if (m.secondaryFrom.has_value() && !m.secondaryTo.has_value())
    {
        _board.remove(m.secondaryFrom.value());
    }

    // Promote if provided
    if (m.promotion.has_value())
    {
        _board.place(m.promotion.value(), c, m.to);
    }

    toggleTurn();
}

void ChessModel::checkEnPassant(const Move m)
{
    auto piece_ptr = atBoardPosition(m.to);
    Color color = piece_ptr->getColor();
    
    // Initial check
    if (!( abs(m.to.y() - m.from.y()) == 2 && piece_ptr->getType() == PieceType::Pawn ))
        return;

    if (color == Color::White)
    {
        if (_board.isInBounds({m.to.x() - 1, m.to.y()}) &&
            _board.isOtherPiece({m.to.x() - 1, m.to.y()}, Color::White))
        {
            _board.setEnPassantTarget({m.to.x(), m.to.y() + 1});
        }
    }
    else if (color == Color::Black)
    {
        if (_board.isInBounds({m.to.x() + 1, m.to.y()}) &&
            _board.isOtherPiece({m.to.x() + 1, m.to.y()}, Color::Black))
        {
            _board.setEnPassantTarget({m.to.x(), m.to.y() - 1});
        }

    }
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



