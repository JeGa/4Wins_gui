/*
* Only one controller is needed to play multiple games.
* How to use:
*
* Register game on controller:
* -> playGame()
* Loop until game is closed:
* -> isRunning()
* Get input for player on turn (who is on turn):
* -> onTurn()
* Make turn:
* -> toggleInput()
* [optional: After game, get winner]:
* -> getWinner()
* 
* Access to the game infos with the function getGame().
*/

#ifndef GAMECONTROLLERSTRATEGY_H
#define GAMECONTROLLERSTRATEGY_H

#include "IGame.h"
#include "IPlayer.h"
#include "IGameController.h"
#include <memory>

namespace controller
{

    class GameControllerStrategy : public IGameController
    {
        private:
            std::shared_ptr<data::IGame> game;

            void convertCoords(int *y);
            // Strategy method to override
            virtual bool checkRow(int x, int y, data::IPlayer *p) = 0;
        public:
            GameControllerStrategy() {}
            virtual ~GameControllerStrategy() {}

            virtual void playGame(std::shared_ptr<data::IGame> game);
            // From field
            virtual std::shared_ptr<data::IPlayer> onTurn();
            // Switches between the 2 players
            virtual bool toggleTurn(int x, int y);
            virtual std::shared_ptr<data::IGame> getGame();
    };

}

#endif // GAMECONTROLLERSTRATEGY_H
