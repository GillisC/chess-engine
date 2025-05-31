#include "pieces/pawn.hpp"


Pawn::Pawn(Color color) : Piece(color) {}

const sf::Texture& Pawn::getTexture(const TextureManager& manager) const 
{
    if (getColor() == WHITE)
    {
        return manager.get("white_pawn");
    }
    return manager.get("black_pawn");
}
