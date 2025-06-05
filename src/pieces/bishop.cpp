#include "pieces/bishop.hpp"


Bishop::Bishop(Color color) : Piece(color) {}

const sf::Texture& Bishop::getTexture(const TextureManager& manager) const 
{
    if (getColor() == WHITE)
    {
        return manager.get("white_bishop");
    }
    return manager.get("black_bishop");
}

std::vector<BoardPosition> Bishop::getValidMoves(ChessBoard& board, const BoardPosition& pos)
{
    std::vector<BoardPosition> validMoves = {};


    return validMoves;
}
