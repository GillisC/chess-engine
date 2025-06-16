#include "pieces/king.hpp"
#include "board.hpp"


King::King(Color color) : Piece(color) {}

PieceType King::getType() 
{
    return PieceType::King;
}

const sf::Texture& King::getTexture(const TextureManager& manager) const 
{
    if (getColor() == White)
    {
        return manager.get("white_king");
    }
    return manager.get("black_king");
}


std::vector<Move> King::getValidMoves(ChessBoard& board, const BoardPosition& pos)
{
    std::vector<Move> validMoves = {};
    
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            BoardPosition offsetPos = {pos.x() + i, pos.y() + j};
            if (board.isInBounds(offsetPos) && !board.isPiece(offsetPos))
            {
                Move validMove = {pos, offsetPos, board};
                validMoves.push_back(validMove);
            }
            else if (board.isInBounds(offsetPos) && board.at(pos)->getColor() != board.at(offsetPos)->getColor())
            {
                Move validMove = {pos, offsetPos, board};
                validMoves.push_back(validMove);
            }
        }
    }
    
    // Castling rules:
    // 1. King and Rook has not been moved
    // 2. The path between King and Rook is clear
    // 3. Castling can't lead to the king being in check
    if (getTimesMoved() == 0)
    {
        // White Queen side castling
        for (int i = 3; i >= 0; i--)
        {
            if (i == 0 && board.isPiece({i ,7}) && board.at({i, 7})->getTimesMoved() == 0)
            {
                Move validMove(pos, {2, 7}, board, BoardPosition(0, 7), BoardPosition(3, 7));
                validMoves.push_back(validMove);
            }
            else if (board.at({i, 7})) // If there is a piece in between
            {
                break;
            }
        }
        
        // White Kingside castling
        for (int i = 5; i <= 7; i++)
        {
            if (i == 7 && board.isPiece({i ,7}) && board.at({i, 7})->getTimesMoved() == 0)
            {
                Move validMove(pos, {6, 7}, board, BoardPosition(7, 7), BoardPosition(5, 7));
                validMoves.push_back(validMove);
            }
            else if (board.at({i, 7})) // If there is a piece in between
            {
                break;
            }
        }


        // Black Queen side castling
        for (int i = 3; i >= 0; i--)
        {
            if (i == 0 && board.isPiece({i ,0}) && board.at({i, 0})->getTimesMoved() == 0)
            {
                Move validMove(pos, {2, 0}, board, BoardPosition(0, 0), BoardPosition(3, 0));
                validMoves.push_back(validMove);
            }
            else if (board.at({i, 0})) // If there is a piece in between
            {
                break;
            }
        }
        
        // Black Kingside castling
        for (int i = 5; i <= 7; i++)
        {
            if (i == 7 && board.isPiece({i ,0}) && board.at({i, 0})->getTimesMoved() == 0)
            {
                Move validMove(pos, {6, 0}, board, BoardPosition(7, 0), BoardPosition(5, 0));
                validMoves.push_back(validMove);
            }
            else if (board.at({i, 0})) // If there is a piece in between
            {
                break;
            }
        }
    }

    return validMoves;
}
