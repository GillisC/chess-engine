#pragma once

#include "color.hpp"
#include "piece_type.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "texture_manager.hpp"
#include "board_position.hpp"

class ChessBoard;

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

    virtual PieceType getType() const = 0;
    virtual const sf::Texture& getTexture(const TextureManager& manager) const = 0;

    virtual std::vector<BoardPosition> getValidMoves(ChessBoard& board, const BoardPosition& pos) = 0;

};
