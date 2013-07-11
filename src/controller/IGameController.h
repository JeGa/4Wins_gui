#ifndef IGAMECONTROLLER_H
#define IGAMECONTROLLER_H

#include "IPlayer.h"
#include "IGame.h"

namespace controller
{

    class IGameController
    {
    public:
        virtual ~IGameController() {};
        
        virtual void playGame(data::IGame *game) = 0;
        virtual bool isRunning() = 0;
        virtual data::IPlayer *onTurn() = 0; // From field
        virtual bool toggleTurn(int x, int y) = 0; // Switches between the 2 players

        virtual data::IPlayer *getLastWinner() = 0;
        virtual data::IGame *getGame() = 0;
    };

}

#endif