#pragma once

#include "board.hpp"
#include <optional>

struct UIState
{
    std::optional<BoardPosition> selectedPiece;
};
