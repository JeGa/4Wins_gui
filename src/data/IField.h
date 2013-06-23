#ifndef IFIELD_H
#define IFIELD_H

#include "ICell.h"
#include <string>

namespace data
{

    class IField
    {
        public:
            virtual ~IField() {}
            virtual void setCellStatus(int x, int y, Colors c) = 0;
            virtual Colors getCellStatus(int x, int y) = 0;
            virtual ICell *getCell(int x, int y) = 0;
            virtual int getWidth() = 0;
            virtual int getHeight() = 0;
            virtual std::string toString() = 0;
    };

}

#endif // IFIELD_H
