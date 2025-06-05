#include "pieces/knight.hpp"


Knight::Knight(Color color) : Piece(color) {}

const sf::Texture& Knight::getTexture(const TextureManager& manager) const 
{
    if (getColor() == WHITE)
    {
        return manager.get("white_knight");
    }
    return manager.get("black_knight");
}


std::vector<BoardPosition> Knight::getValidMoves(ChessBoard& board, const BoardPosition& pos)
{
    std::vector<BoardPosition> validMoves = {};


    return validMoves;
}


