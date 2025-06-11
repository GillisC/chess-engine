#pragma once

#include "piece.hpp"

class Knight: public Piece
{
public:
    Knight(Color color);
    PieceType getType() override;
    const sf::Texture& getTexture(const TextureManager& manager) const override;
    std::vector<Move> getValidMoves(ChessBoard& board, const BoardPosition& pos) override;
};
