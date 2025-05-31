#include "chess_view.hpp"

ChessView::ChessView(ChessModel& model, TextureManager& manager) :
    _model(model), _manager(manager) {}

void ChessView::render(sf::RenderWindow& window)
{
    auto sizeVec = window.getSize();
    int width = sizeVec.x;
    int height = sizeVec.y;
    
    float board_ratio = 0.8;
    int start_pos_x = (width - (width * board_ratio)) / 2;
    int start_pos_y = (height - (height * board_ratio)) / 2;
    float square_side = (width * board_ratio) / 8;
    
    // Render Text
    sf::Font font;
    if (!font.loadFromFile("../assets/fonts/JetBrainsMono-Bold.ttf"))
    {
        throw std::runtime_error("Error loading font");
    }
    
    sf::Text label;
    std::vector<std::string> letters = {"A", "B", "C", "D", "E", "F", "G", "H"};
    std::vector<std::string> numbers = {"1", "2", "3", "4", "5", "6", "7", "8"};
    
    label.setCharacterSize(24);
    label.setFillColor({230, 230, 230, 255});
    label.setFont(font); 

    int letters_start_x = start_pos_x;
    int letters_start_y = start_pos_y + (board_ratio * height);
    
    for (int i = 0; i < 8; i++)
    {
        int squareX = square_side * i + letters_start_x;
        label.setString(letters.at(i));
        sf::FloatRect bounds = label.getLocalBounds();
        label.setOrigin(bounds.left + bounds.width / 2.0f,
                        bounds.top + bounds.height / 2.0f);
        label.setPosition(squareX + square_side / 2.0f, letters_start_y + square_side / 2.0f);
        window.draw(label);
    }
    
    int numbers_start_x = start_pos_x - square_side;
    int numbers_start_y = start_pos_y;

    for (int j = 0; j < 8; j++)
    {
        int squareY = square_side * j + numbers_start_y;
        label.setString(numbers.at(j));
        sf::FloatRect bounds = label.getLocalBounds();
        label.setOrigin(bounds.left + bounds.width / 2.0f,
                        bounds.top + bounds.height / 2.0f);
        label.setPosition(numbers_start_x + square_side / 2.0f, squareY + square_side / 2.0f);
        window.draw(label);
    }
    // Render board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            sf::RectangleShape square(sf::Vector2(square_side, square_side));
            if (i % 2 == 0 && j % 2 == 0) square.setFillColor({230, 230, 230, 255});
            else if (i % 2 != 0 && j % 2 == 0) square.setFillColor({100, 100, 100, 255});
            else if (i % 2 == 0 && j % 2 != 0) square.setFillColor({100, 100, 100, 255});
            else if (i % 2 != 0 && j % 2 == 0) square.setFillColor({230, 230, 255, 255});
            
            int squareX = start_pos_x + square_side * j;
            int squareY = start_pos_y + square_side * i;
            square.setPosition(squareX, squareY);
            window.draw(square);

            // Draw the piece if its there
            auto piece = _model.atBoardPosition({j, i}); 
            if (piece)
            {
                sf::Sprite sprite;
                sprite.setTexture(piece->getTexture(_manager)); 
                auto sprite_bounds = sprite.getLocalBounds();
                
                sprite.setOrigin(
                    sprite_bounds.left + sprite_bounds.width / 2.0f,
                    sprite_bounds.top + sprite_bounds.height / 2.0f
                );
                sprite.setPosition(
                    squareX + square_side / 2.0f,
                    squareY + square_side / 2.0f
                );

               window.draw(sprite);
            }
        }
    }
}
