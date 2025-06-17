#pragma once

#include "color.hpp"
#include "vector"

class ChessBoard;
class Move;

enum class ControllerType
{
    Human,
    Engine
};

class Controller
{
public:
    virtual Move chooseMove(std::vector<Move>& legalMoves, ChessBoard& board) const = 0;
    virtual ControllerType type() const = 0;
    virtual ~Controller() = default;
};
