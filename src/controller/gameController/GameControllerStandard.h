#ifndef GAMECONTROLLERSTANDARD_H
#define GAMECONTROLLERSTANDARD_H

#include "GameControllerStandard.h"
#include "GameControllerStrategy.h"

namespace controller
{

    class GameControllerStandard : public GameControllerStrategy
    {
        private:
            int down(int x, int y, data::IPlayer *p);
            int horizontal(int x, int y, data::IPlayer *p);
            int diagLeftRight(int x, int y, data::IPlayer *p);
            int diagRightLeft(int x, int y, data::IPlayer *p);
            int countCells(int x, int y, data::IPlayer *p, int xDirection, int yDirection);
            bool inField(int x, int y);

            virtual bool checkRow(int x, int y, data::IPlayer *p);
        public:
            GameControllerStandard() {}
            virtual ~GameControllerStandard() {}
    };

}

#endif // GAMECONTROLLERSTANDARD_H
