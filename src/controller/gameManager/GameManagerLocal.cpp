#include "GameManagerLocal.h"

namespace controller
{

    // TODO: Get factory as parameter
    GameManagerLocal::GameManagerLocal() :
        IGameManagerLocal::IGameManagerLocal(new GameFactory()),
        gc(factory->getGameController())
    {   
    }

    bool GameManagerLocal::input(int x, int y)
    {
        return gc->toggleTurn(x, y);
    }
    
    bool GameManagerLocal::setActiveGame(int key)
    {
        try {
            std::shared_ptr<data::IGame>& activeGameRef = games.at(key);

            // Is in map
            gc->playGame(activeGameRef);
        } catch (std::out_of_range& e) {
            // Not in map
            return false;
        }
        return true;
    }

    int GameManagerLocal::getActiveGame()
    {
        return gc->getGame()->getKey();
    }

    std::shared_ptr<data::IGame> GameManagerLocal::getActiveGameRef()
    {
        return gc->getGame();
    }

}