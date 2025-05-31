#include "board.hpp"

ChessBoard::ChessBoard()
{
    _board_data = std::vector(8, std::vector<std::shared_ptr<Piece>>(8));
    
    // Place the white pieces
    place({0,6}, std::make_shared<Pawn>(WHITE));
    place({1,6}, std::make_shared<Pawn>(WHITE));
    place({2,6}, std::make_shared<Pawn>(WHITE));
    place({3,6}, std::make_shared<Pawn>(WHITE));
    place({4,6}, std::make_shared<Pawn>(WHITE));
    place({5,6}, std::make_shared<Pawn>(WHITE));
    place({6,6}, std::make_shared<Pawn>(WHITE));
    place({7,6}, std::make_shared<Pawn>(WHITE));

    place({0, 7}, std::make_shared<Rook>(WHITE));
    place({7, 7}, std::make_shared<Rook>(WHITE));

    place({1, 7}, std::make_shared<Knight>(WHITE));
    place({6, 7}, std::make_shared<Knight>(WHITE));

    place({2, 7}, std::make_shared<Bishop>(WHITE));
    place({5, 7}, std::make_shared<Bishop>(WHITE));
    
    place({3, 7}, std::make_shared<Queen>(WHITE));

    place({4, 7}, std::make_shared<King>(WHITE));

    // Create the black pieces
    place({0,1}, std::make_shared<Pawn>(BLACK));
    place({1,1}, std::make_shared<Pawn>(BLACK));
    place({2,1}, std::make_shared<Pawn>(BLACK));
    place({3,1}, std::make_shared<Pawn>(BLACK));
    place({4,1}, std::make_shared<Pawn>(BLACK));
    place({5,1}, std::make_shared<Pawn>(BLACK));
    place({6,1}, std::make_shared<Pawn>(BLACK));
    place({7,1}, std::make_shared<Pawn>(BLACK));

    place({0, 0}, std::make_shared<Rook>(BLACK));
    place({7, 0}, std::make_shared<Rook>(BLACK));

    place({1, 0}, std::make_shared<Knight>(BLACK));
    place({6, 0}, std::make_shared<Knight>(BLACK));

    place({2, 0}, std::make_shared<Bishop>(BLACK));
    place({5, 0}, std::make_shared<Bishop>(BLACK));
    
    place({3, 0}, std::make_shared<Queen>(BLACK));

    place({4, 0}, std::make_shared<King>(BLACK));
}


void ChessBoard::move(BoardPosition startPos, BoardPosition endPos)
{
    return;
}

void ChessBoard::place(BoardPosition targetPos, std::shared_ptr<Piece> piece_ptr)
{
    _board_data[targetPos.y()][targetPos.x()] = piece_ptr;
}

std::shared_ptr<Piece> ChessBoard::at(const BoardPosition& pos)
{
    if (pos.x() < 0 || pos.x() > 7 || pos.y() < 0 || pos.y() > 7)
    {
        throw std::invalid_argument("Error board position is out of range");
    }

    auto piece = _board_data[pos.y()][pos.x()];
    return piece;
}
void ChessBoard::print() const
{
    
    std::cout << "  " << " A   B   C   D   E   F   G   H " << std::endl;
    std::cout << "  " << "-----------------------------" << std::endl;

    for (int i = 0; i < _board_data.size(); i++)
    {
        std::cout << 8 - i << " ";
        for (int j = 0; j < _board_data[0].size(); j++)
        {
           auto cell = _board_data[i][j];
           if (cell)
           {
               std::cout << "| " << "P" << " ";
           }
           else
           {
               std::cout << "|   ";
           }

        }
        std::cout << "\n";
        std::cout << "  " << "-----------------------------" << std::endl;
    }
}
