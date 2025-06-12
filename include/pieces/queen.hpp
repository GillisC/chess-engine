#pragma once

#include "piece.hpp"

class Queen: public Piece
{
public:
    Queen(Color color);
    PieceType getType() override;
    const sf::Texture& getTexture(const TextureManager& manager) const override;
    std::vector<Move> getValidMoves(ChessBoard& board, const BoardPosition& pos) override;
    

private:
    void queenTravel(ChessBoard &board, const BoardPosition startPos, int xDir, int yDir, std::vector<Move> &moveVec);
};
