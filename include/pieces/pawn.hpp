#pragma once

#include "piece.hpp"

class Pawn : public Piece
{
public:
    Pawn(Color color);
    PieceType getType() const override;
    const sf::Texture& getTexture(const TextureManager& manager) const override;    
    std::vector<BoardPosition> getValidMoves(ChessBoard& board, const BoardPosition& pos) override;
};
