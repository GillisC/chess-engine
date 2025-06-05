#include "../include/chess_model.hpp"

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
    if (!isPiece(pos))
    {
        return validMoves; 
    }

    auto piece = atBoardPosition(pos);

    if (dynamic_cast<Pawn*>(piece.get()))
    {
        std::cout << "Clicked a pawn" << std::endl;
        int xCord = pos.x();
        int yCord = pos.y();

        if (piece->getColor() == Color::WHITE)
        {
            if (!isPiece({xCord, yCord - 1}) && yCord > 0) validMoves.push_back(BoardPosition({xCord, yCord - 1}));
        }
    }
    return validMoves;
}


void ChessModel::movePiece(const BoardPosition& from, const BoardPosition& to)
{
    _board.move(from, to);
}

