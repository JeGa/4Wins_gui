#include "GameManagerLocal.h"

namespace controller
{

    GameManagerLocal::GameManagerLocal(IGameController *gc)
    {
        this->gc = gc;
    }

    GameManagerLocal::~GameManagerLocal()
    {
        clear();
    }
    
    void GameManagerLocal::newGame(data::IGame *game)
    {
        if (gc == nullptr)
            return;
            
        if (gc->getGame() != nullptr) {
            if (game->getPlayer1() != gc->getGame()->getPlayer1())
                delete gc->getGame()->getPlayer1();
            if (game->getPlayer2() != gc->getGame()->getPlayer2())
                delete gc->getGame()->getPlayer2();
            
            delete gc->getGame();
        }
        
        gc->playGame(game);
    }
    
    // Frees all memory
    void GameManagerLocal::clear()
    {
        if (gc) {
            if (gc->getGame()) {
                if (gc->getGame()->getPlayer1())
                    delete gc->getGame()->getPlayer1();
                if (gc->getGame()->getPlayer2())
                    delete gc->getGame()->getPlayer2();

                delete gc->getGame();
            }
            
            delete gc;
            gc = nullptr;
        }
    }
    
    IGameController *GameManagerLocal::getGameController()
    {
        return gc;
    }
    
    bool GameManagerLocal::input(int x, int y)
    {
        if (gc != nullptr)
            return gc->toggleTurn(x, y);
        return false;
    }

    data::IGame *GameManagerLocal::getGame()
    {
        return gc->getGame();
    }

}