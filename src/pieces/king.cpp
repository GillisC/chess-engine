#include "pieces/king.hpp"
#include "board.hpp"


King::King(Color color) : Piece(color) {}

PieceType King::getType() const 
{
    return PieceType::King;
}

const sf::Texture& King::getTexture(const TextureManager& manager) const 
{
    if (getColor() == White)
    {
        return manager.get("white_king");
    }
    return manager.get("black_king");
}


std::vector<BoardPosition> King::getValidMoves(ChessBoard& board, const BoardPosition& pos)
{
    std::vector<BoardPosition> validMoves = {};
    
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            BoardPosition offsetPos = {pos.x() + i, pos.y() + j};
            if (board.isInBounds(offsetPos) && !board.isPiece(offsetPos))
            {
                validMoves.push_back(offsetPos);
            }
            else if (board.isInBounds(offsetPos) && board.at(pos)->getColor() != board.at(offsetPos)->getColor())
            {
                validMoves.push_back(offsetPos);
            }
        }
    }

    return validMoves;
}
