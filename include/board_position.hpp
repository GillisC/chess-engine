#pragma once

#include <memory.h>
#include <stdexcept>

// Class representing positions on the board
class BoardPosition
{
    int _x, _y;

public:
    BoardPosition(int x, int y) : _x(x), _y(y) {}
    BoardPosition(std::initializer_list<int> list)
    {
        if (list.size() != 2)
        {
            throw std::invalid_argument("BoardPosition required exactly 2 elements");
        }
        auto iterator = list.begin();
        _x = *iterator++;
        _y = *iterator;
    }

    int x() const { return _x; }
    int y() const { return _y; }

    static std::string positionToNotation(const BoardPosition& pos)
    {
        if (pos.x() < 0 || pos.x() > 7 || pos.y() < 0 || pos.y() > 7)
        {
            throw std::out_of_range("BoardPosition is out of bounds");
        }

        char file = 'a' + pos.x();     // 'a' through 'h'
        char rank = '1' + pos.y();     // '1' through '8'

        return std::string{file, rank};
    }

    static BoardPosition notationToPosition(std::string& pos)
    {
        if (pos.size() != 2)
        {
            throw std::invalid_argument("Error pos is not of size 2");
        }

        int col = pos[0] - 'a';
        int row = pos[1] - '1';

        return BoardPosition({col, row});
    }

    bool operator==(const BoardPosition& other) const
    {
        return (_x == other.x() && _y == other.y());
    }
};
