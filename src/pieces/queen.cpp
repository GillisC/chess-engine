#include "pieces/queen.hpp"


Queen::Queen(Color color) : Piece(color) {}

const sf::Texture& Queen::getTexture(const TextureManager& manager) const 
{
    if (getColor() == WHITE)
    {
        return manager.get("white_queen");
    }
    return manager.get("black_queen");
}
