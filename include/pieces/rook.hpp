#pragma once

#include "piece.hpp"

class Rook: public Piece
{
public:
    Rook(Color color);
    PieceType getType() override;
    const sf::Texture& getTexture(const TextureManager& manager) const override;
    std::vector<Move> getValidMoves(ChessBoard& board, const BoardPosition& pos) override;

private:

    // Utility function which gathers the valid moves for the rook
    void rookTravel(ChessBoard& board, const BoardPosition startPos, int xDir, int yDir, std::vector<Move>& moveVec);
};
