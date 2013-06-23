#ifndef IGAME_H
#define IGAME_H

#include "IPlayer.h"
#include <string>

namespace data
{

    class IGame
    {
        public:
            virtual ~IGame() {}
            virtual IPlayer *onTurn() = 0;
            virtual IPlayer *notOnTurn() = 0;
            virtual void setCellStatus(int x, int y, IPlayer *player) = 0; // Wrapper for field
            virtual IPlayer *getCellStatus(int x, int y) = 0; // Wrapper for field
            virtual IPlayer *getPlayer1() = 0;
            virtual IPlayer *getPlayer2() = 0;
            virtual int getWidth() = 0;
            virtual int getHeight() = 0;
            virtual std::string toString() = 0;
    };

}

#endif // IGAME_H
