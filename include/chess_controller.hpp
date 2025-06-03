#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "chess_model.hpp"
#include "config.hpp"
#include "uistate.hpp"

// The ChessController gets handed events by the main loop and updates the model or view
// To do this it gets passed a pointer to the model.
class ChessController
{
    ChessModel& _model;
    UIState& _uiState;

public:
    ChessController(ChessModel& model, UIState& uiState);
    void handleEvent(sf::Event& event);
};
