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
            BoardPosition targetPos = {xCord, yCord - 1};
            if (yCord - 1 == 0)
            {
                Move prom1(pos, targetPos, board, std::nullopt, std::nullopt, PieceType::Rook);
                Move prom2(pos, targetPos, board, std::nullopt, std::nullopt, PieceType::Bishop);
                Move prom3(pos, targetPos, board, std::nullopt, std::nullopt, PieceType::Knight);
                Move prom4(pos, targetPos, board, std::nullopt, std::nullopt, PieceType::Queen);
                validMoves.push_back(prom1);
                validMoves.push_back(prom2);
                validMoves.push_back(prom3);
                validMoves.push_back(prom4);
            }
            else 
            {
                Move validMove(pos, targetPos, board);
                validMoves.push_back(validMove);
            }
        }
        // Move two steps forward
        if (board.isInBounds({xCord, yCord - 2}) && 
            piece->getTimesMoved() == 0 && 
            !board.isPiece({xCord, yCord - 2})) 
        {
            std::cout << "what" << std::endl;
            Move validMove(pos, {xCord, yCord - 2}, board);
            validMoves.push_back(validMove);
        }
        if (board.isInBounds({xCord - 1, yCord - 1}) &&
            board.isBlack({xCord - 1, yCord - 1}))
        {
            Move validMove(pos, {xCord - 1, yCord - 1}, board);
            validMoves.push_back(validMove);
        }
        if (board.isInBounds({xCord + 1, yCord - 1}) &&
            board.isBlack({xCord + 1, yCord - 1})) 
        {
            Move validMove(pos, {xCord + 1, yCord - 1}, board);
            validMoves.push_back(validMove);
        }
        // White en passant left
        if (board.isInBounds({xCord - 1, yCord - 1}) &&
            board.isEnPassantTarget({xCord - 1, yCord - 1}))
        {
            Move validMove(pos, {xCord - 1, yCord - 1}, board, BoardPosition(xCord - 1, yCord), std::nullopt);
            validMoves.push_back(validMove);
        }
        // White en passant right
        if (board.isInBounds({xCord + 1, yCord - 1}) &&
            board.isEnPassantTarget({xCord + 1, yCord - 1}))
        {
            Move validMove(pos, {xCord + 1, yCord - 1}, board, BoardPosition(xCord + 1, yCord), std::nullopt);
            validMoves.push_back(validMove);
        }
    }
    else if (piece->getColor() == Color::Black)
    {
        if (board.isInBounds({xCord, yCord + 1})&& !board.isPiece({xCord, yCord + 1}))
        {
            BoardPosition targetPos = {xCord, yCord + 1};
            if (yCord + 1 == 7)
            {
                Move prom1(pos, targetPos, board, std::nullopt, std::nullopt, PieceType::Rook);
                Move prom2(pos, targetPos, board, std::nullopt, std::nullopt, PieceType::Bishop);
                Move prom3(pos, targetPos, board, std::nullopt, std::nullopt, PieceType::Knight);
                Move prom4(pos, targetPos, board, std::nullopt, std::nullopt, PieceType::Queen);
                validMoves.push_back(prom1);
                validMoves.push_back(prom2);
                validMoves.push_back(prom3);
                validMoves.push_back(prom4);
            }
            else
            {
                Move validMove(pos, targetPos, board);
                validMoves.push_back(validMove);
            }
        }
        // Move two steps forward
        if (board.isInBounds({xCord, yCord + 2}) && (piece->getTimesMoved() == 0))
        {
            Move validMove(pos, {xCord, yCord + 2}, board);
            validMoves.push_back(validMove);
        }
        if (board.isInBounds({xCord - 1, yCord + 1}) && board.isWhite({xCord - 1, yCord + 1})) 
        {
            Move validMove(pos, {xCord - 1, yCord + 1}, board);
            validMoves.push_back(validMove);
        }
        if (board.isInBounds({xCord + 1, yCord + 1}) && board.isWhite({xCord + 1, yCord + 1}))
        {
            Move validMove(pos, {xCord + 1, yCord + 1}, board);
            validMoves.push_back(validMove);
        }
        // Black en passant left
        if (board.isInBounds({xCord - 1, yCord + 1}) &&
            board.isEnPassantTarget({xCord - 1, yCord + 1}))
        {
            Move validMove(pos, {xCord - 1, yCord + 1}, board, BoardPosition(xCord - 1, yCord), std::nullopt);
            validMoves.push_back(validMove);
        }
        // Black en passant right
        if (board.isInBounds({xCord + 1, yCord + 1}) &&
            board.isEnPassantTarget({xCord + 1, yCord + 1}))
        {
            Move validMove(pos, {xCord + 1, yCord + 1}, board, BoardPosition(xCord + 1, yCord), std::nullopt);
            validMoves.push_back(validMove);
        }
    }

    return validMoves;
}
