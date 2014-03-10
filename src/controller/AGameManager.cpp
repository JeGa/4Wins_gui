#include "AGameManager.h"
#include <boost/lexical_cast.hpp>

namespace controller
{

    AGameManager::AGameManager(GameFactory *f) : factory(f)
    {
    }

    int controller::AGameManager::addGame(std::shared_ptr<data::IGame> g)
    {
        int key = g->getKey();
        games[key] = g;
        return key;
    }

    void controller::AGameManager::clearPlayers()
    {
        players.clear();
    }

    void controller::AGameManager::clearGames()
    {
        games.clear();
    }

    int controller::AGameManager::addPlayer(std::string name, std::string pw)
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

    int controller::AGameManager::addGame(int p1Key, int p2Key)
    {
        std::shared_ptr<data::IGame> g(factory->getGameDefault(
                                           players[p1Key],
                                           players[p2Key],
                                           players[p1Key]
                                       ));
        return addGame(g);
    }

    int controller::AGameManager::addGame(int p1Key, int p2Key, int width, int height)
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

    std::map<int, std::shared_ptr<data::IGame>>& controller::AGameManager::getGames()
    {
        return games;
    }

    std::map<int, std::shared_ptr<data::IPlayer>>& controller::AGameManager::getPlayers()
    {
        return players;
    }

    std::string controller::AGameManager::toString()
    {
        std::string strGames;
        std::string strPlayers;

        strGames = "Games:\n";
        for (auto i : games) {
            strGames += boost::lexical_cast<std::string>(i.first);
            strGames += " | " + i.second->getPlayer1()->getName();
            strGames += " <-> " + i.second->getPlayer2()->getName();
            strGames += "\n";
        }
        strPlayers = "Players:\n";
        for (auto i : players) {
            strPlayers += boost::lexical_cast<std::string>(i.first);
            strPlayers += " | " + i.second->getName();
            strPlayers += "\n";
        }

        return (strGames + "\n\n" + strPlayers);
    }

}
