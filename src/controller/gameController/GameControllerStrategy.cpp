#include "GameControllerStrategy.h"

#include "IGame.h"
#include "IPlayer.h"
#include <iostream>

namespace controller
{

    GameControllerStrategy::GameControllerStrategy() :
        lastWinner(NULL), game(nullptr) {}

    GameControllerStrategy::~GameControllerStrategy() {}

    void GameControllerStrategy::playGame(data::IGame *game)
    {
        this->game = game;
    }

    bool GameControllerStrategy::toggleTurn(int x, int y)
    {
        if (!game->isRunning())
            return false;
            
        convertCoords(&y);

        // Check if valid cell
        int h = game->getHeight();

        // Cell not free
        if (game->getCellStatus(x, y) != NULL)
            return false;

        // Bottom
        if (y != h-1) {
            // Has to be over a set cell
            if (game->getCellStatus(x, y+1) == NULL)
                return false;
        }

        // Set cell (changes onTurn!!)
        game->setCellStatus(x, y, game->onTurn());

        // Check if win (because of the last set cell, so last turn player is needed)
        if (checkRow(x, y, game->notOnTurn())) {
            if (game->notOnTurn() == game->getPlayer1()) {
                // P1 Wins
                game->getPlayer1()->addGameStatistic(data::IPlayer::WIN);
                game->getPlayer2()->addGameStatistic(data::IPlayer::LOOSE);
                lastWinner = game->getPlayer1();
            } else {
                // P2 Wins
                game->getPlayer2()->addGameStatistic(data::IPlayer::WIN);
                game->getPlayer1()->addGameStatistic(data::IPlayer::LOOSE);
                lastWinner = game->getPlayer2();
            }

            game->setRunning(false);
        }

        return true;
    }

    data::IPlayer *GameControllerStrategy::onTurn()
    {
        return game->onTurn();
    }

    bool GameControllerStrategy::isRunning()
    {
        if (game != nullptr)
            return game->isRunning();
        return false;
    }

    data::IPlayer *GameControllerStrategy::getLastWinner()
    {
        return lastWinner;
    }

    data::IGame *GameControllerStrategy::getGame()
    {
        return game;
    }

    /*
    * Converts the coordinates to the real coordinates for the array.
    * (real begins with 0,0 from top-left, easier is from bottom-left)
    */
    void GameControllerStrategy::convertCoords(int *y)
    {
        *y = game->getHeight() -1 - *y;
    }

}
