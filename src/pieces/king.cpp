#include "pieces/king.hpp"


King::King(Color color) : Piece(color) {}

const sf::Texture& King::getTexture(const TextureManager& manager) const 
{
    if (getColor() == WHITE)
    {
        return manager.get("white_king");
    }
    return manager.get("black_king");
}


std::vector<BoardPosition> King::getValidMoves(ChessBoard& board, const BoardPosition& pos)
{
    std::vector<BoardPosition> validMoves = {};


    return validMoves;
}
