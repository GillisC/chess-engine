#include "pieces/pawn.hpp"
#include "board.hpp"


Pawn::Pawn(Color color) : Piece(color) {}


PieceType Pawn::getType() 
{
    return PieceType::Pawn;
}

const sf::Texture& Pawn::getTexture(const TextureManager& manager) const 
{
    if (getColor() == White)
    {
        return manager.get("white_pawn");
    }
    return manager.get("black_pawn");
}

std::vector<Move> Pawn::getValidMoves(ChessBoard& board, const BoardPosition& pos)
{
    std::vector<Move> validMoves = {};
    auto piece = board.at(pos);
    int xCord = pos.x();
    int yCord = pos.y();

    if (piece->getColor() == Color::White)
    {
        if (board.isInBounds({xCord, yCord - 1}) &&
            !board.isPiece({xCord, yCord - 1})) 
        {
            Move validMove = {pos, {xCord, yCord - 1}};
            validMoves.push_back(validMove);
        }

        if (board.isInBounds({xCord, yCord - 2}) && 
            piece->getTimesMoved() == 0 && 
            !board.isPiece({xCord, yCord - 2})) 
        {
            Move validMove = {pos, {xCord, yCord - 2}};
            validMoves.push_back(validMove);
        }
        if (board.isInBounds({xCord - 1, yCord - 1}) &&
            board.isBlack({xCord - 1, yCord - 1}))
        {
            Move validMove = {pos, {xCord - 1, yCord - 1}};
            validMoves.push_back(validMove);
        }
        if (board.isInBounds({xCord + 1, yCord - 1}) &&
            board.isBlack({xCord + 1, yCord - 1})) 
        {
            Move validMove = {pos, {xCord + 1, yCord - 1}};
            validMoves.push_back(validMove);
        }
    }
    else if (piece->getColor() == Color::Black)
    {
        if (board.isInBounds({xCord, yCord + 1})&& !board.isPiece({xCord, yCord + 1}))
        {
            Move validMove = {pos, {xCord, yCord + 1}};
            validMoves.push_back(validMove);
        }
        if (board.isInBounds({xCord, yCord + 2}) && (piece->getTimesMoved() == 0))
        {
            Move validMove = {pos, {xCord, yCord + 2}};
            validMoves.push_back(validMove);
        }
        if (board.isInBounds({xCord - 1, yCord + 1}) && board.isWhite({xCord - 1, yCord + 1})) 
        {
            Move validMove = {pos, {xCord - 1, yCord + 1}};
            validMoves.push_back(validMove);
        }
        if (board.isInBounds({xCord + 1, yCord + 1}) && board.isWhite({xCord + 1, yCord + 1}))
        {
            Move validMove = {pos, {xCord + 1, yCord + 1}};
            validMoves.push_back(validMove);
        }
    }

    return validMoves;
}
