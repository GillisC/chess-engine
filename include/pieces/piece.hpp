#pragma once

#include "../color.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "../texture_manager.hpp"

class Piece
{
    Color _color;
    unsigned int _moved = 0; // The number of times the piece has been moved;

public:

    Piece(Color color) : _color(color) {}
    virtual ~Piece() = default;

    Color getColor() const { return _color; }
    unsigned int getTimesMoved() const { return _moved; }
    void incrementMoved() { _moved++; }

    virtual const sf::Texture& getTexture(const TextureManager& manager) const = 0;

};
