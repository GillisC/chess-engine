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
    
    bool operator==(const BoardPosition& other)
    {
        return (_x == other.x() && _y == other.y());
    }
};
