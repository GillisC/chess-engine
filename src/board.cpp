#include "board.hpp"


ChessBoard::ChessBoard()
{
    _board_data = std::vector(8, std::vector<std::shared_ptr<Piece>>(8));
    
    // Place the white pieces
    place({0,6}, std::make_shared<Pawn>(White));
    place({1,6}, std::make_shared<Pawn>(White));
    place({2,6}, std::make_shared<Pawn>(White));
    place({3,6}, std::make_shared<Pawn>(White));
    place({4,6}, std::make_shared<Pawn>(White));
    place({5,6}, std::make_shared<Pawn>(White));
    place({6,6}, std::make_shared<Pawn>(White));
    place({7,6}, std::make_shared<Pawn>(White));

    place({0, 7}, std::make_shared<Rook>(White));
    place({7, 7}, std::make_shared<Rook>(White));

    place({1, 7}, std::make_shared<Knight>(White));
    place({6, 7}, std::make_shared<Knight>(White));

    place({2, 7}, std::make_shared<Bishop>(White));
    place({5, 7}, std::make_shared<Bishop>(White));
    
    place({3, 7}, std::make_shared<Queen>(White));

    place({4, 7}, std::make_shared<King>(White));

    // Create the black pieces
    place({0,1}, std::make_shared<Pawn>(Black));
    place({1,1}, std::make_shared<Pawn>(Black));
    place({2,1}, std::make_shared<Pawn>(Black));
    place({3,1}, std::make_shared<Pawn>(Black));
    place({4,1}, std::make_shared<Pawn>(Black));
    place({5,1}, std::make_shared<Pawn>(Black));
    place({6,1}, std::make_shared<Pawn>(Black));
    place({7,1}, std::make_shared<Pawn>(Black));

    place({0, 0}, std::make_shared<Rook>(Black));
    place({7, 0}, std::make_shared<Rook>(Black));

    place({1, 0}, std::make_shared<Knight>(Black));
    place({6, 0}, std::make_shared<Knight>(Black));

    place({2, 0}, std::make_shared<Bishop>(Black));
    place({5, 0}, std::make_shared<Bishop>(Black));
    
    place({3, 0}, std::make_shared<Queen>(Black));

    place({4, 0}, std::make_shared<King>(Black));
}


void ChessBoard::move(BoardPosition startPos, BoardPosition endPos)
{
    _board_data[endPos.y()][endPos.x()] = _board_data[startPos.y()][startPos.x()];
    _board_data[startPos.y()][startPos.x()] = nullptr;
}

void ChessBoard::place(BoardPosition targetPos, std::shared_ptr<Piece> piece_ptr)
{
    _board_data[targetPos.y()][targetPos.x()] = piece_ptr;
}

std::shared_ptr<Piece> ChessBoard::at(const BoardPosition& pos)
{
    if (pos.x() < 0 || pos.x() > 7 || pos.y() < 0 || pos.y() > 7)
    {
        throw std::invalid_argument("Error board position is out of range");
    }

    auto piece = _board_data[pos.y()][pos.x()];
    return piece;
}

bool ChessBoard::isPiece(const BoardPosition& pos)
{
    return at(pos) != nullptr;
}

bool ChessBoard::isWhite(const BoardPosition& pos)
{
    return isPiece(pos) && at(pos)->getColor() == Color::White;
}

bool ChessBoard::isBlack(const BoardPosition& pos)
{
    return isPiece(pos) && at(pos)->getColor() == Color::Black;
}

bool ChessBoard::isInBounds(const BoardPosition& pos)
{
    return (pos.x() >= 0 && pos.x() < 8 && pos.y() >= 0 && pos.y() < 8);
}
