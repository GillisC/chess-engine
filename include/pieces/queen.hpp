#pragma once

#include "piece.hpp"

class Queen: public Piece
{
public:
    Queen(Color color);
    const sf::Texture& getTexture(const TextureManager& manager) const override;
    std::vector<BoardPosition> getValidMoves(ChessBoard& board, const BoardPosition& pos) override;
};
