/*
* Up from this class IPlayer is uesd to identify palyers.
* The enum Colors is only used internal.
*/

#ifndef GAME_H
#define GAME_H

#include "IGame.h"
#include "IField.h"
#include <string>

namespace data
{

    class Game : public IGame
    {
        private:
            IField *field;
            IPlayer *player1;
            IPlayer *player2;
            IPlayer *turn;
        public:
            Game(IField *field, IPlayer *player1, IPlayer *player2, IPlayer *onTurn);
            virtual ~Game();
            virtual IPlayer *onTurn();
            virtual IPlayer *notOnTurn();

            virtual void setCellStatus(int x, int y, IPlayer *player);
            virtual IPlayer *getCellStatus(int x, int y);

            virtual IPlayer *getPlayer1();
            virtual IPlayer *getPlayer2();
            virtual int getWidth();
            virtual int getHeight();
            virtual std::string toString();
    };

}

#endif // GAME_H
