#include "pieces/knight.hpp"
#include "board.hpp"


Knight::Knight(Color color) : Piece(color) {}

const sf::Texture& Knight::getTexture(const TextureManager& manager) const 
{
    if (getColor() == WHITE)
    {
        return manager.get("white_knight");
    }
    return manager.get("black_knight");
}


std::vector<BoardPosition> Knight::getValidMoves(ChessBoard& board, const BoardPosition& pos)
{
    std::vector<BoardPosition> validMoves = {};
    
    int x = pos.x();
    int y = pos.y();
    std::vector<BoardPosition> moveOffsets =
    {
        {x - 2, y - 1},
        {x - 2, y + 1},
        
        {x - 1, y - 2},
        {x - 1, y + 2},
        
        {x + 1, y - 2},
        {x + 1, y + 2},
        
        {x + 2, y - 1},
        {x + 2, y + 1}
    };

    for (BoardPosition offset : moveOffsets)
    {
        if (board.isInBounds(offset) && !board.isPiece(offset))
        {
            validMoves.push_back(offset);
        }
        else if (board.isInBounds(offset) && board.at(pos)->getColor() != board.at(offset)->getColor())
        {
            validMoves.push_back(offset);
        }
    }

    return validMoves;
}


