#ifndef CELL_H
#define CELL_H

#include "ICell.h"
#include <string>

namespace data
{

    class Cell : public ICell
    {
        private:
            Colors color;
        public:
            Cell(Colors c);
            Cell();
            virtual ~Cell() {}
            virtual void setColor(Colors c);
            virtual Colors getColor();
            virtual std::string toString();

            Cell& operator=(Cell& other) = delete;
            Cell(Cell& other) = delete;
    };

}

#endif // CELL_H
