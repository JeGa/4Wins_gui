#ifndef AGAMEMANAGER_H
#define AGAMEMANAGER_H

#include <map>

namespace controller
{
    
    class AGameManager
    {
    protected:
        std::map<int, data::IGame *> games;
        std::map<int, data::IPlayer *> players;
    public:
        std::map<int, data::IGame *> getGames()
        {
            return games;
        }
    
        std::map<int, data::IPlayer *> getPlayers()
        {
            return players;
        } 
    };
    
}

#endif