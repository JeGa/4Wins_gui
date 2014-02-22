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
        int addGame(std::shared_ptr<data::IGame> g)
        {
            int key = g->getKey();
            games[key] = g;
            return key;
        }

    protected:
        std::map<int, std::shared_ptr<data::IGame>> games;
        std::map<int, std::shared_ptr<data::IPlayer>> players;

        std::unique_ptr<GameFactory> factory;

        void clearPlayers()
        {
            players.clear();
        }

        void clearGames()
        {
            games.clear();
        }

        /*
        * Adds the player to the map if he is not in the map.
        */
        int addPlayer(std::string name, std::string pw)
        {
            std::shared_ptr<data::IPlayer> p(factory->getPlayer(name, pw));

            try {
                players.at(p->getKey());

                // Already in map
            } catch (std::out_of_range& e) {
                // Add to map
                players[p->getKey()] = p;
            }

            return p->getKey();
        }

        int addGame(int p1Key, int p2Key)
        {
            std::shared_ptr<data::IGame> g(factory->getGameDefault(
                players[p1Key],
                players[p2Key],
                players[p1Key]
            ));
            return addGame(g);
        }

        int addGame(int p1Key, int p2Key, int width, int height)
        {
            std::shared_ptr<data::IGame> g(factory->getGame(
                width,
                height,
                players[p1Key],
                players[p2Key],
                players[p1Key]
            ));
            return addGame(g);
        }

    public:
        AGameManager(GameFactory *f) : factory(f) {}

        std::map<int, std::shared_ptr<data::IGame>>& getGames()
        {
            return games;
        }

        std::map<int, std::shared_ptr<data::IPlayer>>& getPlayers()
        {
            return players;
        }
    };

}

#endif