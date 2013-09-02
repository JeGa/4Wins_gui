/*
* The GameFactory given in the constructor specifies the implementation used
* for the instantiated GameManager class.
*/

#ifndef AGAMEMANAGER_H
#define AGAMEMANAGER_H

#include <map>
#include <memory>

namespace controller
{
    
    class AGameManager
    {
    public:
        AGameManager(GameFactory& f) : factory(f) {}

        std::map<int, std::unique_ptr<data::IGame>> getGames()
        {
            return games;
        }
    
        std::map<int, std::unique_ptr<data::IPlayer>> getPlayers()
        {
            return players;
        }

    protected:
        std::map<int, std::unique_ptr<data::IGame>> games;
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
        * Returns the key from the player.
        */
        int addPlayer(std::string name, std::string pw)
        {
            auto p = std::make_shared<data::IPlayer>(factory.getPlayer(name, pw));

            try {
                players.at(p->getKey());

                // Already in map
            } catch (std::out_of_range& e) {

                // Add to map
                players[p->getKey()] = p;
            }

            return p->getKey();
        }

        /*
        * Adds a new game.
        * Returns the key from the game.
        */
        int addGame(int p1Key, int p2Key)
        {
            std::unique_ptr<data::IGame> g(factory.getGameDefault(
                players[p1Key],
                players[p2Key],
                players[p1Key]
            ));

            games[g->getKey()] = std::move(g);
        }

        int addGame(int p1Key, int p2Key, int x, int y)
        {
            std::unique_ptr<data::IGame> g(factory.getGame(
                x,
                y,
                players[p1Key],
                players[p2Key],
                players[p1Key]
            ));

            games[g->getKey()] = std::move(g);
        }
    };
    
}

#endif