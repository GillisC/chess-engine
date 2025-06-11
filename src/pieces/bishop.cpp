#include "pieces/bishop.hpp"
#include "board.hpp"

Bishop::Bishop(Color color) : Piece(color) {}

PieceType Bishop::getType() 
{
    return PieceType::Bishop;
}

const sf::Texture& Bishop::getTexture(const TextureManager& manager) const 
{
    if (getColor() == White)
    {
        return manager.get("white_bishop");
    }
    return manager.get("black_bishop");
}

std::vector<Move> Bishop::getValidMoves(ChessBoard& board, const BoardPosition& pos)
{
    std::vector<Move> validMoves = {};

    bishopTravel(board, pos, -1, -1, validMoves);
    bishopTravel(board, pos, 1, -1, validMoves);
    bishopTravel(board, pos, 1, 1, validMoves);
    bishopTravel(board, pos, -1, 1, validMoves);

    return validMoves;
}


void Bishop::bishopTravel(ChessBoard &board, const BoardPosition startPos, int xDir, int yDir, std::vector<Move> &moveVec) 
{
    for (int i = 1; i < 8; i++) 
    {
        BoardPosition offsetPos = {startPos.x() + (xDir * i),
            startPos.y() + yDir * i};
        if (board.isInBounds(offsetPos)) 
        {
            if (!(board.isPiece(offsetPos))) 
            {
                Move validMove = {startPos, offsetPos};
                moveVec.push_back(validMove);
            } else if (board.at(offsetPos)->getColor() ==
                    board.at(startPos)->getColor()) 
            {
                break;
            } else if (board.at(offsetPos)->getColor() !=
                    board.at(startPos)->getColor()) 
            {
                Move validMove = {startPos, offsetPos};
                moveVec.push_back(validMove);
                break;
            }
        } else
            break;
    }
}
