#pragma once

#include "piece.hpp"

class Rook: public Piece
{
public:
    Rook(Color color);
    const sf::Texture& getTexture(const TextureManager& manager) const override;
};
