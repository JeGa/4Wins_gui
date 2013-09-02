#include "GameManagerLocal.h"

namespace controller
{

    GameManagerLocal::GameManagerLocal(GameFactory& f) :
        IGameManagerLocal(f),
        gc(factory->getGameController())
    { }

    GameManagerLocal::~GameManagerLocal()
    {
        clear();
    }

    bool GameManagerLocal::playerStatus(std::string name, std::string pw)
    {
        data::IPlayer *p = factory.getPlayer(name, pw);
        bool status = false;

        try {
            data::IPlayer *tmp = players.at(p->getKey());
            // Player in list

            tmp->setLoggedIn(playerStatus);

            status = true;
        } catch (std::out_of_range& e) {
            // Player not in list
        }

        delete p;
        return status;
    }
    
    bool GameManagerLocal::newGame(std::string p1, std::string p2)
    {
        if (p1 == "" || p2 == "")
            return false;

        int p1Key = addPlayer(p1, "");
        int p2Key = addPlayer(p2, "");
        int gameKey = addGame(p1Key, p2Key);




        // If game is not in the map add it
        if (games.find(game->getKey()) == games.end()) {
            games.insert(std::pair<int, data::IGame*>(game->getKey(), game));
        }



        
        // If player is not in the map add it
        addPlayer(game->getPlayer1());
        addPlayer(game->getPlayer2());
        
        // Set active
        gc->playGame(game);
    }
    
    bool GameManagerLocal::input(int x, int y)
    {
        if (gc != nullptr)
            return gc->toggleTurn(x, y);
        return false;
    }
    
    bool GameManagerLocal::setActiveGame(data::IGame *game)
    {
        if (game == nullptr) {
            gc->playGame(nullptr);
            return true;
        }
        
        if (games.find(game->getKey()) == games.end())
            return false;
        
        gc->playGame(game);
        
        return true;
    }
    
    bool GameManagerLocal::deleteGame(data::IGame *game)
    {
        int key = game->getKey();
        
        if (games.count(key) != 1)
            return false;
            
        data::IGame *g = games.at(key);
        // If the to be deleted game is the active game, remove it as active
        // game
        if (this->getActiveGame() == g) {
            this->setActiveGame(nullptr);
        }
        delete g;
        
        games.erase(key);
        
        return true;
    }
    
    // Frees all memory
    void GameManagerLocal::clear()
    {
        for (auto i = games.begin(); i != games.end(); i++) {
            delete i->second;
        }
        
        for (auto i = players.begin(); i != players.end(); i++) {
            delete i->second;
        }
        
        players.clear();
        games.clear();
        
        if (gc) {
            delete gc;
            gc = nullptr;
        }
    }
    
    void GameManagerLocal::addPlayer(data::IPlayer *player)
    {
        if (players.find(player->getKey()) == players.end()) {
            players.insert(std::pair<int, data::IPlayer *>(player->getKey(), player));
        }
    }

    data::IGame *GameManagerLocal::getActiveGame()
    {
        return gc->getGame();
    }

}