#include "Field.h"
#include "ICell.h"

#include <string>
#include <stdexcept>

namespace data
{

    Field::Field(ICell ***cell_field, int x, int y)
        : cell_field(cell_field), width(x), height(y)
    {

    }

    Field::~Field()
    {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j< height; j++) {
                delete cell_field[i][j];
            }
            delete[] cell_field[i];
        }

        delete[] cell_field;
    }

    bool Field::checkInField(int x, int y)
    {
        if (x >= 0 && x < width && y >= 0 && y < height)
            return true;
        return false;
    }

    void Field::setCellStatus(int x, int y, Colors c)
    {
        if (!checkInField(x, y))
            throw std::out_of_range("Index not valid.");

        cell_field[x][y]->setColor(c);
    }

    Colors Field::getCellStatus(int x, int y)
    {
        if (!checkInField(x, y))
            throw std::out_of_range("Index not valid.");

        return cell_field[x][y]->getColor();
    }

    ICell *Field::getCell(int x, int y)
    {
        if (!checkInField(x, y))
            throw std::out_of_range("Index not valid.");

        return cell_field[x][y];
    }

    int Field::getWidth()
    {
        return width;
    }

    int Field::getHeight()
    {
        return height;
    }

    std::string Field::toString()
    {
        std::string str("");


        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                str += cell_field[i][j]->toString();
            }
            str += "\n";
        }

        return str;
    }

}
