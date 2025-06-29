#include "chess_view.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

ChessView::ChessView(ChessModel& model, TextureManager& manager, UIState& uiState) :
    _model(model), _manager(manager), _uiState(uiState) 
{
}

void ChessView::render(sf::RenderWindow& window)
{
    auto sizeVec = window.getSize();
    int width = sizeVec.x;
    int height = sizeVec.y;
    
    int start_pos_x = (width - (width * Config::Config::BoardAspectRatio)) / 2;
    int start_pos_y = (height - (height * Config::BoardAspectRatio)) / 2;
    float square_side = (width * Config::BoardAspectRatio) / 8;
    
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
    int letters_start_y = start_pos_y + (Config::BoardAspectRatio * height);
    
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

    std::optional<BoardPosition> selectedPiece = _uiState.selectedPiece;

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

            if (selectedPiece && j == selectedPiece->x() && i == selectedPiece->y())
            {
                square.setFillColor(sf::Color::Blue);
                window.draw(square);
            }
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

    // Draw indicators for the current available moves
    if (_uiState.selectedPiece.has_value())
    {
        auto validMoves = _model.getMoves(_uiState.selectedPiece.value());

        sf::CircleShape indicatorCircle(square_side / 4.0f);
        for (auto move : validMoves)
        {
            int squareX = start_pos_x + square_side * move.to.x();
            int squareY = start_pos_y + square_side * move.to.y();

            sf::FloatRect indicatorBounds = indicatorCircle.getLocalBounds();
            indicatorCircle.setOrigin(
                indicatorBounds.left + indicatorBounds.width / 2.0f,
                indicatorBounds.top + indicatorBounds.height / 2.0f
            );

            indicatorCircle.setPosition(squareX + square_side / 2.0f, squareY + square_side / 2.0f);
            indicatorCircle.setFillColor({ 31, 31, 31, 100 });

            window.draw(indicatorCircle);

        }
    }
    if (_uiState.promotionMove.has_value())
    {
        renderPromotionUI(window);
    }
}

void ChessView::renderPromotionUI(sf::RenderWindow& window)
{
    sf::Texture queenTex, rookTex, bishopTex, knightTex;
    int spriteIndex;
    if (_model.getTurn() == Color::White)
       spriteIndex = 0; 
    else
        spriteIndex = 4;

    BoardPosition promoteSquare = _uiState.promotionMove.value()->to;
     
    auto sizeVec = window.getSize();
    int width = sizeVec.x;
    
    float square_side = (width * Config::BoardAspectRatio) / 8;
    float boxX = getSideMargin(window) + square_side * promoteSquare.x() + square_side * 0.5;
    float boxY = getSideMargin(window) + square_side * 2 + square_side * 0.5;

    _uiState.promotionSprites[spriteIndex].first.setPosition(boxX, boxY);
    _uiState.promotionSprites[spriteIndex + 1].first.setPosition(boxX, boxY + square_side);
    _uiState.promotionSprites[spriteIndex + 2].first.setPosition(boxX, boxY + (square_side * 2));
    _uiState.promotionSprites[spriteIndex + 3].first.setPosition(boxX, boxY + (square_side * 3));

    // Draw a box background
    sf::RectangleShape box(sf::Vector2f(square_side, square_side * 4));
    box.setPosition(boxX - square_side * 0.5, boxY - square_side * 0.5);
    box.setFillColor({210, 210, 210, 200});
    box.setOutlineColor({31, 31, 31, 255});
    box.setOutlineThickness(3.f);
    window.draw(box);

    window.draw(_uiState.promotionSprites[spriteIndex].first);
    window.draw(_uiState.promotionSprites[spriteIndex + 1].first);
    window.draw(_uiState.promotionSprites[spriteIndex + 2].first);
    window.draw(_uiState.promotionSprites[spriteIndex + 3].first);
}

float ChessView::getBoardSideLength(sf::RenderWindow& window)
{
    return window.getSize().x * Config::BoardAspectRatio;
}

float ChessView::getSideMargin(sf::RenderWindow& window)
{
    auto windowSizeVec = window.getSize();
    return ( windowSizeVec.x - (window.getSize().x * Config::BoardAspectRatio) ) / 2;
}
    
