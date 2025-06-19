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
            else if (board.isInBounds(offsetPos) && board.at(pos) && board.at(pos)->getColor() != board.at(offsetPos)->getColor())
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
        if (board.at(pos)->getColor() == Color::White)
        {
            // White Queen side castling
            if (!board.at("d8") &&
                !board.at("c8") &&
                !board.at("b8") &&
                 board.at("a8") &&
                 board.at("a8")->getTimesMoved() == 0)
            {
                Move validMove(pos, {2, 7}, board, BoardPosition(0, 7), BoardPosition(3, 7));
                validMoves.push_back(validMove);
            }

            // White Kingside castling
            if (!board.at("f8") &&
                !board.at("g8") &&
                 board.at("h8") &&
                 board.at("h8")->getTimesMoved() == 0)
            {
                Move validMove(pos, {6, 7}, board, BoardPosition(7, 7), BoardPosition(5, 7));
                validMoves.push_back(validMove);
            }
        }

        else if (board.at(pos)->getColor() == Color::Black)
        {
            // Black Queen side castling
            if (!board.at("d1") &&
                !board.at("c1") &&
                !board.at("b1") &&
                 board.at("a1") &&
                 board.at("a1")->getTimesMoved() == 0)
            {
                Move validMove(pos, {2, 0}, board, BoardPosition(0, 0), BoardPosition(3, 0));
                validMoves.push_back(validMove);
            }

            // Black Kingside castling
            if (!board.at("f1") &&
                !board.at("g1") &&
                 board.at("h1") &&
                 board.at("h1")->getTimesMoved() == 0)
            {
                Move validMove(pos, {6, 0}, board, BoardPosition(7, 0), BoardPosition(5, 0));
                validMoves.push_back(validMove);
            }
        }
    }
    return validMoves;
}
