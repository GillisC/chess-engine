#include "chess_controller.hpp"
#include "SFML/System/Vector2.hpp"
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

            const sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

            if (_uiState.promotionMove.has_value())
            {
                for (auto& pair : _uiState.promotionSprites) 
                {
                    if (pair.first.getGlobalBounds().contains(mousePos))
                    {
                        _uiState.promotionMove.value()->promotion = pair.second;
                        _model.executeMove( *(_uiState.promotionMove.value()) );
                        _uiState.promotionMove.reset();
                        _uiState.selectedPiece.reset();
                        break;
                    }
                }
                return; // Locks the player into choosing promotion type
            }

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

                if (_model.isPiece({xCord, yCord}) && 
                    _model.atBoardPosition({xCord, yCord})->getColor() == _model.getTurn())
                {
                    _uiState.selectedPiece = BoardPosition({xCord, yCord});
                    auto validMoves = _model.getMoves({xCord, yCord});
                    std::cout << "Valid moves len: " << validMoves.size() << std::endl;

                }
                else if (_uiState.selectedPiece.has_value())
                {
                    // If the square pressed is a valid move for the selected piece, move the piece there
                    auto currentValidMoves = _model.getMoves(_uiState.selectedPiece.value());
                    const auto selectedSquare = BoardPosition({xCord, yCord});

                    // Get the Move object that corresponds to the pressed valid square
                    auto it = std::find_if(
                            currentValidMoves.begin(),
                            currentValidMoves.end(),
                            [&selectedSquare](const Move& m) {
                            return m.to == selectedSquare;
                            }
                            );

                    if (it != currentValidMoves.end())
                    {
                        const Move& move = *it;
                        if (move.promotion.has_value())
                        {
                            std::cout << "Player chose a promotion move" << std::endl;
                           // Render the promotion UI and wait for player action
                           _uiState.promotionMove = std::make_shared<Move>(move);
                            return;
                        }
                        _model.executeMove(move);
                    }
                }
            }
        }
    }
}

