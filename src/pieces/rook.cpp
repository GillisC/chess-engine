#include "pieces/rook.hpp"


Rook::Rook(Color color) : Piece(color) {}

const sf::Texture& Rook::getTexture(const TextureManager& manager) const 
{
    if (getColor() == WHITE)
    {
        return manager.get("white_rook");
    }
    return manager.get("black_rook");
}
