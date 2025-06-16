#pragma once

#include <optional>
#include <memory>
#include "board_position.hpp"
#include "piece_type.hpp"
#include "pieces/piece.hpp"

class ChessBoard;
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
    const BoardPosition from;
    const BoardPosition to;
    std::shared_ptr<Piece> primaryPiece;
 
    std::optional<std::shared_ptr<Piece>> captured;
    
    std::optional<const BoardPosition> secondaryFrom;
    std::optional<const BoardPosition> secondaryTo;
    std::optional<std::shared_ptr<Piece>> secondaryPiece;

    std::optional<PieceType> promotion;

    Move(
        const BoardPosition f, 
        const BoardPosition t,
        ChessBoard& board,
        std::optional<const BoardPosition> sf = std::nullopt,
        std::optional<const BoardPosition> st = std::nullopt, 
        std::optional<PieceType> p = std::nullopt
    );
};
