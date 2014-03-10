#ifndef IGAMEMANAGERSERVER_H
#define IGAMEMANAGERSERVER_H

#include "IGame.h"
#include "IPlayer.h"
#include "TCPConnection.h"
#include "AGameManager.h"
#include <vector>
#include <memory>

namespace controller
{
    
    class IGameManagerServer : public AGameManager
    {
    public:
        IGameManagerServer(GameFactory *f) : AGameManager(f) {}
        virtual ~IGameManagerServer() {};
        
        virtual void start() = 0;
        virtual void stop() = 0;

        // TODO: Smart pointer
        virtual void newGame(data::IGame *game) = 0;
        virtual bool deleteGame(data::IGame *game) = 0;
        virtual bool input(int x, int y) = 0;

        virtual bool setActiveGame(data::IGame *game) = 0;
        virtual data::IGame *getActiveGame() = 0;
        
        virtual std::vector<std::shared_ptr<TCPConnection>>& getConnections() = 0;
    };
    
}

#endif