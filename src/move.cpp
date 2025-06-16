#include "move.hpp"
#include "board.hpp"

Move::Move(
        const BoardPosition f, 
        const BoardPosition t,
        ChessBoard& board,
        std::optional<const BoardPosition> sf,
        std::optional<const BoardPosition> st,
        std::optional<PieceType> p
    )
    : from(f)
    , to(t)
    , secondaryFrom(sf)
    , secondaryTo(st)
    , promotion(p)
{
    primaryPiece = board.at(f);

    if (board.isOtherPiece(t, primaryPiece->getColor()))
    {
        captured = board.at(t);
    }
    if (secondaryFrom)
    {
        secondaryPiece = board.at(secondaryFrom.value());
    }
}
