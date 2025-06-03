#include "chess_app.hpp"


ChessApp::ChessApp()
    : _window(sf::VideoMode(Config::WindowWidth, Config::WindowHeight), "ChessEngine")
    , _uiState()
    , _textureManager()
    , _model()
    , _view(_model, _textureManager, _uiState)
    , _controller(_model, _uiState)
{
    // Temporary
    _window.setPosition({2440, 200});

    _textureManager.load("black_pawn",   "../assets/sprites/black_pawn.png");
    _textureManager.load("white_pawn",   "../assets/sprites/white_pawn.png");

    _textureManager.load("white_rook",   "../assets/sprites/white_rook.png");
    _textureManager.load("black_rook",   "../assets/sprites/black_rook.png");

    _textureManager.load("white_knight", "../assets/sprites/white_knight.png");
    _textureManager.load("black_knight", "../assets/sprites/black_knight.png");

    _textureManager.load("white_bishop", "../assets/sprites/white_bishop.png");
    _textureManager.load("black_bishop", "../assets/sprites/black_bishop.png");

    _textureManager.load("white_queen",  "../assets/sprites/white_queen.png");
    _textureManager.load("black_queen",  "../assets/sprites/black_queen.png");

    _textureManager.load("white_king",   "../assets/sprites/white_king.png");
    _textureManager.load("black_king",   "../assets/sprites/black_king.png");
}


void ChessApp::start()
{
    _window.setFramerateLimit(60);

    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            _controller.handleEvent(event);

            if (event.type == sf::Event::Closed) 
            {
                _window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    _window.close();
                }
            }

        }

        _window.clear({31, 31, 31, 255});

        _view.render(_window);

        _window.display();
    }
}
