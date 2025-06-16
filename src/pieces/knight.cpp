#include "pieces/knight.hpp"
#include "board.hpp"


Knight::Knight(Color color) : Piece(color) {}

PieceType Knight::getType() 
{
    return PieceType::Knight;
}

const sf::Texture& Knight::getTexture(const TextureManager& manager) const 
{
    if (getColor() == Color::White)
    {
        return manager.get("white_knight");
    }
    return manager.get("black_knight");
}


std::vector<Move> Knight::getValidMoves(ChessBoard& board, const BoardPosition& pos)
{
    std::vector<Move> validMoves = {};
    
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
            Move validMove(pos, offset, board); 
            validMoves.push_back(validMove);
        }
        else if (board.isInBounds(offset) && board.at(pos)->getColor() != board.at(offset)->getColor())
        {
            Move validMove(pos, offset, board);
            validMoves.push_back(validMove);
        }
    }

    return validMoves;
}


