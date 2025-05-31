#pragma once

#include "piece.hpp"


class Pawn : public Piece
{
public:
    Pawn(Color color);
    const sf::Texture& getTexture(const TextureManager& manager) const override;    
};
