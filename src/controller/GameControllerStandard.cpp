#include "GameControllerStandard.h"

#include <iostream>

namespace controller
{

    bool GameControllerStandard::checkRow(int x, int y, data::IPlayer *p)
    {
        // Functions return number of player-cells in a row (if >= 4: Win!)

        if (diagLeftRight(x, y, p) >= 4)
            return true;
        if (diagRightLeft(x, y, p) >= 4)
            return true;
        if (horizontal(x, y, p) >= 4)
            return true;
        if (down(x, y, p) >= 4)
            return true;

        return false;
    }

    int GameControllerStandard::down(int x, int y, data::IPlayer *p)
    {
        return countCells(x, y, p, 0, 1);
    }

    int GameControllerStandard::horizontal(int x, int y, data::IPlayer *p) // '-'
    {
        int sum = 0;

        sum = countCells(x, y, p, -1, 0);
        sum += countCells(x+1, y, p, +1, 0);
        // (dont count double)

        return sum;
    }

    int GameControllerStandard::diagLeftRight(int x, int y, data::IPlayer *p) // '/'
    {
        int sum = 0;

        sum = countCells(x, y, p, -1, +1); // First to left down
        sum += countCells(x+1, y-1, p, +1, -1); // Than to right up
        // (dont count double)

        return sum;
    }

    int GameControllerStandard::diagRightLeft(int x, int y, data::IPlayer *p) // '\'
    {
        int sum = 0;

        countCells(x, y, p, +1, +1); // First to right down
        countCells(x-1, y-1, p, -1, -1); // Than to left up
        // (dont count double)

        return sum;
    }

    int GameControllerStandard::countCells(int x, int y, data::IPlayer *p, int xDirection, int yDirection)
    {
        int sum = 0;

        //std::cout << "Size::: " << getGame()->getWidth() << " " << getGame()->getHeight() << std::endl;
        //std::cout << "## countCells: " << x << " " << y << " with direction: " << xDirection << " " << yDirection << std::endl;
        //std::cout << "## In field: " << inField(x, y) << " cell status: " << getGame()->getCellStatus(x, y) << " player: "<< p <<std::endl;

        while (inField(x, y) && (getGame()->getCellStatus(x, y) == p)) {
            sum++;

            x += xDirection;
            y += yDirection;
            //std::cout << "-> countCellsLoop: " << x << " " << y << " sum: " << sum << std::endl;
        }

        return sum;
    }

    bool GameControllerStandard::inField(int x, int y)
    {
        if (x >= 0 && x < getGame()->getWidth() && y >= 0 && y < getGame()->getHeight())
            return true;
        return false;
    }

}
