#ifndef ICELL_H
#define ICELL_H

#include <string>

namespace data
{

    enum Colors {PLAYER1 = 0, PLAYER2, NOTSET};
    static const char *colorsChar[] = {"X", "O", "-"};

    class ICell
    {
        public:
            virtual ~ICell() {}
            virtual void setColor(Colors c) = 0;
            virtual Colors getColor() = 0;
            virtual std::string toString() = 0;

            ICell() = default;
            ICell& operator=(ICell& other) = delete;
            ICell(ICell& other) = delete;
    };

}

#endif // ICELL_H
