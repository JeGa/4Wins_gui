#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "IGameManager.h"
#include "IGame.h"
#include "IPlayer.h"
#include "IGameController.h"
#include <map>

namespace controller
{
    
    class GameManagerNetwork : public IGameManager
    {
    private:
        //NetworkManager
        data::IPlayer *player;
        std::map<int, data::IGame*> games;
        std::map<int, data::IPlayer*> otherPlayers;
    public:
        GameManagerNetwork(data::IPlayer *player, IGameController *gc);
        // server adress, ...
        virtual ~GameManagerNetwork();
        
        virtual void newGame(data::IGame *game) {};
        virtual IGameController *getGameController() {};
        virtual bool input(int x, int y) {};
        // set input() -> send to server, copy in games
    };

}

#endif // GAMEMANAGER_H
