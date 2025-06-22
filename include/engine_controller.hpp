#pragma once

#include <random>
#include <algorithm>

#include "controller.hpp"
#include "move.hpp"
#include "board.hpp"
#include "piece_square_tables.hpp"

class EngineController : public Controller
{
public:
    Move chooseMove(std::vector<Move>& legalMoves, ChessBoard& board) override;
    ControllerType type() const override { return ControllerType::Engine; }

private:
    int materialEvalutation(ChessBoard& board);
    int pieceValue(std::shared_ptr<Piece> piece);

    int piecePlacementEvaluation(ChessBoard& board);
    int placementValue(PieceType type, Color color, const BoardPosition pos);
};
