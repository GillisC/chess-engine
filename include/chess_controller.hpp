#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "chess_model.hpp"

// The ChessController gets handed events by the main loop and updates the model or view
// To do this it gets passed a pointer to the model.
class ChessController
{
    ChessModel& _model;
    
public:
    ChessController(ChessModel& model);
    void handleEvent(sf::Event& event);
};
