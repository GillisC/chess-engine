#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "config.hpp"
#include "uistate.hpp"
#include "chess_model.hpp"
#include "chess_view.hpp"
#include "chess_controller.hpp"
#include "texture_manager.hpp"

// The main application for the chess engine
class ChessApp
{
    sf::RenderWindow _window; 
    UIState _uiState;
    TextureManager _textureManager;
    ChessModel _model;
    ChessView _view;
    ChessController _controller;

public:
    ChessApp();
    void start();

private:
    void initPromotionSpriteMap();
    void centerOrigin(sf::Sprite& sprite);
};
