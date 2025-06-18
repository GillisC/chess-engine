#pragma once

#include "board.hpp"
#include <optional>
#include <SFML/Graphics.hpp>

struct UIState
{
    std::optional<BoardPosition> selectedPiece;

    // This is set by the controller when a human player moves to promote a pawn
    // If a BoardPosition is set then the view renders the appropriate UI elements
    std::optional<std::shared_ptr<Move>> promotionMove;

    // Populated by the view, when a promotion is active the view alters the sprite's positions
    // and draws them. The controller can then determine which piece the player chose.
    std::vector<std::pair<sf::Sprite, PieceType>> promotionSprites;
};
