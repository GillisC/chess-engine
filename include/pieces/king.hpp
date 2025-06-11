#pragma once

#include "piece.hpp"

class King : public Piece
{
public:
    King(Color color);
    PieceType getType() override;
    const sf::Texture& getTexture(const TextureManager& manager) const override;
    std::vector<Move> getValidMoves(ChessBoard& board, const BoardPosition& pos) override;
};
