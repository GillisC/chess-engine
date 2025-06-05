#include "chess_controller.hpp"
#include "board.hpp"


ChessController::ChessController(ChessModel& model, UIState& uiState) : _model(model), _uiState(uiState) {}


void ChessController::handleEvent(sf::Event& event)
{
    
    if (event.type == sf::Event::KeyPressed)
    {
        std::cout << "Keyboard input" << std::endl;
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Mouse has been pressed at: x="
                      << event.mouseButton.x << ", "
                      << "y=" << event.mouseButton.y
                      << std::endl;

            // Get the square that was clicked
            unsigned int board_width = Config::WindowWidth * Config::BoardAspectRatio;
            unsigned int board_height = Config::WindowHeight * Config::BoardAspectRatio;
            auto square_side_len = board_width / 8.0f;

            if (event.mouseButton.x > (Config::WindowWidth - board_width) / 2.0f &&
                event.mouseButton.x < board_width + (Config::WindowWidth - board_width) / 2.0f &&
                event.mouseButton.y > (Config::WindowHeight - board_height) / 2.0f &&
                event.mouseButton.y < board_height + (Config::WindowHeight - board_height) / 2.0f)
            {
                // Get the pressed board square index
                int xCord = (event.mouseButton.x - (Config::WindowWidth - board_width) / 2.0f) / square_side_len;
                int yCord = (event.mouseButton.y - (Config::WindowHeight - board_height) / 2.0f) / square_side_len;
                std::cout << "xCord=" << xCord << ", yCord=" << yCord << std::endl;

                if (_model.isPiece({xCord, yCord}))
                {
                    _uiState.selectedPiece = BoardPosition({xCord, yCord});
                    auto validMoves = _model.getMoves({xCord, yCord});
                    std::cout << "Valid moves len: " << validMoves.size() << std::endl;

                }
                else if (!_model.isPiece({xCord, yCord}) && _uiState.selectedPiece.has_value())
                {
                    auto currentValidMoves = _model.getMoves(_uiState.selectedPiece.value());
                    auto selectedSquare = BoardPosition({xCord, yCord});
                    if (std::find(currentValidMoves.begin(), currentValidMoves.end(), selectedSquare) != currentValidMoves.end())
                    {
                        _model.movePiece(_uiState.selectedPiece.value(), selectedSquare);
                    }
                }
            }
        }
    }
}

