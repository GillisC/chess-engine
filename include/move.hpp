#pragma once

#include <optional>
#include "board_position.hpp"
#include "piece_type.hpp"

// Holds the data for performing a move
// from is the starting position of the primary piece
// to is the valid position of the primary piece
// secondaryFrom is an optional member which specifies another piece starting position
// secondaryTo is to where the secondary piece should be moved if the move is executed
// promotion specifies which type the given piece should be promoted to
//
// When a promotion move is generated the promotion field is first set to nullopt
// The controller then handles which PieceType that is set by the user before executing the move.
struct Move
{
    BoardPosition from;
    BoardPosition to;
    std::optional<BoardPosition> secondaryFrom;
    std::optional<BoardPosition> secondaryTo;
    std::optional<PieceType> promotion;

    Move(BoardPosition f, BoardPosition t,
            std::optional<BoardPosition> sf = std::nullopt,
            std::optional<BoardPosition> st = std::nullopt,
            std::optional<PieceType> p = std::nullopt)
        : from(f), to(t), secondaryFrom(sf), secondaryTo(st), promotion(p) {}
};
