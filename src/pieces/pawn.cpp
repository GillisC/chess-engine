#include "pieces/pawn.hpp"
#include "board.hpp"


Pawn::Pawn(Color color) : Piece(color) {}


PieceType Pawn::getType() const {
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

std::vector<BoardPosition> Pawn::getValidMoves(ChessBoard& board, const BoardPosition& pos)
{
    std::vector<BoardPosition> validMoves = {};
    auto piece = board.at(pos);
    int xCord = pos.x();
    int yCord = pos.y();

    if (piece->getColor() == Color::White)
    {
        if (board.isInBounds({xCord, yCord - 1}) &&
            !board.isPiece({xCord, yCord - 1})) 
        {
            validMoves.push_back({xCord, yCord - 1});
        }

        if (board.isInBounds({xCord, yCord - 2}) && 
            piece->getTimesMoved() == 0 && 
            !board.isPiece({xCord, yCord - 2})) 
        {
            validMoves.push_back({xCord, yCord - 2});
        }
        if (board.isInBounds({xCord - 1, yCord - 1}) &&
            board.isBlack({xCord - 1, yCord - 1}))
        {
            validMoves.push_back({xCord - 1, yCord - 1});
        }
        if (board.isInBounds({xCord + 1, yCord - 1}) &&
            board.isBlack({xCord + 1, yCord - 1})) 
        {
            validMoves.push_back({xCord + 1, yCord - 1});
        }
    }
    else if (piece->getColor() == Color::Black)
    {
        if (board.isInBounds({xCord, yCord + 1})&& !board.isPiece({xCord, yCord + 1}))
        {
            validMoves.push_back({xCord, yCord + 1});
        }
        if (board.isInBounds({xCord, yCord + 2}) && (piece->getTimesMoved() == 0))
        {
            validMoves.push_back({xCord, yCord + 2});
        }
        if (board.isInBounds({xCord - 1, yCord + 1}) && board.isWhite({xCord - 1, yCord + 1})) 
        {
            validMoves.push_back({xCord - 1, yCord + 1});
        }
        if (board.isInBounds({xCord + 1, yCord + 1}) && board.isWhite({xCord + 1, yCord + 1}))
        {
            validMoves.push_back({xCord + 1, yCord + 1});
        }
    }

    return validMoves;
}
