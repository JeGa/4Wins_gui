/*
* TODO:
* The GameFactory given in the constructor specifies the implementation
* used for the instantiated GameManager class.
*
* TODO:
* Maybe a getPlayer().
*
* TODO:
* Maybe deleteGame().
*
* TODO:
* Delete Player.
*/

#ifndef AGAMEMANAGER_H
#define AGAMEMANAGER_H

#include <map>
#include <memory>
#include <stdexcept>
#include "GameFactory.h"

namespace controller
{

    class AGameManager
    {
    private:
        int addGame(std::shared_ptr<data::IGame> g);

    protected:
        std::map<int, std::shared_ptr<data::IGame>> games;
        std::map<int, std::shared_ptr<data::IPlayer>> players;
        std::unique_ptr<GameFactory> factory;

        void clearPlayers();
        void clearGames();

        // Adds the player to the map if he is not in the map.
        int addPlayer(std::string name, std::string pw);
        int addGame(int p1Key, int p2Key);
        int addGame(int p1Key, int p2Key, int width, int height);
    public:
        AGameManager(GameFactory *f);
        virtual ~AGameManager() {};

        std::map<int, std::shared_ptr<data::IGame>>& getGames();
        std::map<int, std::shared_ptr<data::IPlayer>>& getPlayers();
    };

}

#endif