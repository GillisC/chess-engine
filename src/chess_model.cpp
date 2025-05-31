#include "../include/chess_model.hpp"
#include <memory>

ChessModel::ChessModel() : 
    _board(std::make_shared<ChessBoard>())
    {}


std::shared_ptr<Piece> ChessModel::atBoardPosition(const BoardPosition& pos)
{
    return _board->at(pos);
}
