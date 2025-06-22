#pragma once

#include "controller.hpp"
#include "move.hpp"
#include <stdexcept>

class HumanController : public Controller
{
public:

    // This will not be executed, move execution is handled by the ui for a human controller
    Move chooseMove(std::vector<Move>& legalMoves, ChessBoard& board) override
    { 
        throw std::logic_error("HumanController: chooseMove should not be executed");
        return legalMoves[0];
    }

    ControllerType type() const override { return ControllerType::Human; }
};
