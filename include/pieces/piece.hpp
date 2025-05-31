#pragma once

#include "../color.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "../texture_manager.hpp"

class Piece
{
    Color _color;
public:

    Piece(Color color) : _color(color) {}
    virtual ~Piece() = default;

    Color getColor() const { return _color; }

    virtual const sf::Texture& getTexture(const TextureManager& manager) const = 0;
};
