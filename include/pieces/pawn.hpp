#pragma once

#include "piece.hpp"
#include "move.hpp"

class Pawn : public Piece
{
public:
    Pawn(Color color);
    PieceType getType() override;
    const sf::Texture& getTexture(const TextureManager& manager) const override;    
    std::vector<Move> getValidMoves(ChessBoard& board, const BoardPosition& pos) override;
};
