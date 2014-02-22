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
        
        virtual void playGame(std::shared_ptr<data::IGame> game) = 0;
        virtual std::shared_ptr<data::IPlayer> onTurn() = 0;
        virtual bool toggleTurn(int x, int y) = 0;
        virtual std::shared_ptr<data::IGame> getGame() = 0;
    };

}

#endif