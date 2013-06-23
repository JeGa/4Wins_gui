#ifndef FIELD_H
#define FIELD_H

#include "IField.h"
#include <string>

namespace data
{

    class Field : public IField
    {
        private:
            ICell ***cell_field;
            int width;
            int height;

            bool checkInField(int x, int y);
        public:
            Field(ICell ***cell_field, int x, int y);
            virtual ~Field();

            virtual void setCellStatus(int x, int y, Colors c);
            virtual Colors getCellStatus(int x, int y);
            virtual ICell *getCell(int x, int y);
            virtual int getWidth();
            virtual int getHeight();
            virtual std::string toString();
    };

}

#endif // FIELD_H
