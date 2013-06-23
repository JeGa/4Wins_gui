#ifndef ICELL_H
#define ICELL_H

#include <string>

namespace data
{

    enum Colors {PLAYER1, PLAYER2, NOTSET};

    class ICell
    {
        public:
            virtual ~ICell() {}
            virtual void setColor(Colors c) = 0;
            virtual Colors getColor() = 0;
            virtual std::string toString() = 0;
    };

}

#endif // ICELL_H
