#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "chess_model.hpp"
#include "texture_manager.hpp"
#include <stdexcept>


// The ChessView renders the state of the ChessModel
// To do this it gets passed a pointer to the model.
class ChessView
{
    ChessModel& _model;
    TextureManager& _manager;
    
public:
    ChessView(ChessModel& model, TextureManager& manager);
    void render(sf::RenderWindow& window);
};
