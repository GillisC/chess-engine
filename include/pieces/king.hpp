#pragma once

#include "piece.hpp"

class King : public Piece
{
public:
    King(Color color);
    const sf::Texture& getTexture(const TextureManager& manager) const override;
};
