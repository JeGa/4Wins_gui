#include "Cell.h"

#include <string>

namespace data
{

    Cell::Cell()
    {
        color = NOTSET;
    }

    Cell::Cell(Colors c)
    {
        color = c;
    }

    void Cell::setColor(Colors c)
    {
        color = c;
    }

    Colors Cell::getColor()
    {
        return color;
    }

    std::string Cell::toString()
    {
        if (color == PLAYER1)
            return "X";
        if (color == PLAYER2)
            return "O";
        if (color == NOTSET)
            return "-";
        return "R";
    }

}
