#ifndef IGAMECONTROLLER_H
#define IGAMECONTROLLER_H

#include "IPlayer.h"
#include "IGame.h"
#include <memory>

namespace controller
{

    class IGameController
    {
    public:
        virtual ~IGameController() {};
        
        virtual void playGame(data::IGame *game) = 0;
        virtual std::shared_ptr<data::IPlayer> onTurn() = 0; // From field
        virtual bool toggleTurn(int x, int y) = 0; // Switches between the 2 players
        virtual data::IGame *getGame() = 0;
    };

}

#endif