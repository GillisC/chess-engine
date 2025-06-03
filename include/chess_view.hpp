#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "config.hpp"
#include "chess_model.hpp"
#include "texture_manager.hpp"
#include <stdexcept>
#include "uistate.hpp"

// The ChessView renders the state of the ChessModel
// To do this it gets passed a pointer to the model.
class ChessView
{
    ChessModel& _model;
    TextureManager& _manager;
    UIState& _uiState;
    
public:
    ChessView(ChessModel& model, TextureManager& manager, UIState& uiState);
    void render(sf::RenderWindow& window);
};
