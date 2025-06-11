#include "pieces/queen.hpp"
#include "board.hpp"


Queen::Queen(Color color) : Piece(color) {}


PieceType Queen::getType() 
{
    return PieceType::Queen;
}

const sf::Texture& Queen::getTexture(const TextureManager& manager) const 
{
    if (getColor() == White)
    {
        return manager.get("white_queen");
    }
    return manager.get("black_queen");
}

std::vector<BoardPosition> Queen::getValidMoves(ChessBoard& board, const BoardPosition& pos)
{
    std::vector<BoardPosition> validMoves = {};

    // Straight
    queenTravel(board, pos, -1, 0, validMoves);
    queenTravel(board, pos, 0, -1, validMoves);
    queenTravel(board, pos, 1, 0, validMoves);
    queenTravel(board, pos, 0, 1, validMoves);
    // Diagonal
    queenTravel(board, pos, -1, -1, validMoves);
    queenTravel(board, pos, 1, -1, validMoves);
    queenTravel(board, pos, 1, 1, validMoves);
    queenTravel(board, pos, -1, 1, validMoves);

    return validMoves;
}


void Queen::queenTravel(ChessBoard &board, const BoardPosition startPos, int xDir, int yDir, std::vector<BoardPosition> &moveVec) 
{
    for (int i = 1; i < 8; i++) 
    {
        BoardPosition offsetPos = {startPos.x() + (xDir * i),
            startPos.y() + yDir * i};
        if (board.isInBounds(offsetPos)) 
        {
            if (!(board.isPiece(offsetPos))) 
            {
                moveVec.push_back(offsetPos);
            } else if (board.at(offsetPos)->getColor() ==
                    board.at(startPos)->getColor()) 
            {
                break;
            } else if (board.at(offsetPos)->getColor() !=
                    board.at(startPos)->getColor()) 
            {
                moveVec.push_back(offsetPos);
                break;
            }
        } else
            break;
    }
}
