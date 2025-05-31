#pragma once


#include "board.hpp"

class ChessModel
{
    std::shared_ptr<ChessBoard> _board;
public:
    ChessModel();

    // Returns the piece at the provided BoardPosition
    // If there isn't a piece present it will return nullptr
    std::shared_ptr<Piece> atBoardPosition(const BoardPosition& pos);
};
