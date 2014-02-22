#include "GameControllerStrategy.h"

#include "IGame.h"
#include "IPlayer.h"
#include <iostream>

namespace controller
{

    void GameControllerStrategy::playGame(std::shared_ptr<data::IGame> game)
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
        if (checkRow(x, y, game->notOnTurn().get())) {
            if (game->notOnTurn() == game->getPlayer1()) {
                // P1 Wins
                game->getPlayer1()->addGameStatistic(data::IPlayer::WIN);
                game->getPlayer2()->addGameStatistic(data::IPlayer::LOOSE);
                game->setWinner(game->getPlayer1()->getKey());
            } else {
                // P2 Wins
                game->getPlayer2()->addGameStatistic(data::IPlayer::WIN);
                game->getPlayer1()->addGameStatistic(data::IPlayer::LOOSE);
                game->setWinner(game->getPlayer2()->getKey());
            }

            game->setRunning(false);
        }

        return true;
    }

    std::shared_ptr<data::IPlayer> GameControllerStrategy::onTurn()
    {
        return game->onTurn();
    }

    std::shared_ptr<data::IGame> GameControllerStrategy::getGame()
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