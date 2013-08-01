#ifndef IGAMEMANAGERSERVER_H
#define IGAMEMANAGERSERVER_H

#include "IGame.h"
#include "IPlayer.h"
#include "TCPConnection.h"
#include <vector>
#include <memory>
#include "AGameManager.h"

namespace controller
{
    
    class IGameManagerServer : public AGameManager
    {
    public:
        virtual ~IGameManagerServer() {};
        
        virtual void start() = 0;
        virtual void stop() = 0;
        
        virtual void newGame(data::IGame *game) = 0;
        virtual bool deleteGame(data::IGame *game) = 0;
        virtual bool input(int x, int y) = 0;
        virtual bool setActiveGame(data::IGame *game) = 0;
        virtual data::IGame *getActiveGame() = 0;
        
        virtual std::vector<std::unique_ptr<TCPConnection>>& getConnections() = 0;
    };
    
}

#endif