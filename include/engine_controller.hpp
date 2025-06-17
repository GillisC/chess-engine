#pragma once

#include "controller.hpp"
#include "move.hpp"
#include <random>

class EngineController : public Controller
{
public:
    Move chooseMove(std::vector<Move>& legalMoves, ChessBoard& board) const override;
    ControllerType type() const override { return ControllerType::Engine; }
};
