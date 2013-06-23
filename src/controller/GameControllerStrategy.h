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
* -> getLastWinner()
*/

#ifndef GAMECONTROLLERSTRATEGY_H
#define GAMECONTROLLERSTRATEGY_H

#include "IGame.h"
#include "IPlayer.h"

namespace controller
{

    class GameControllerStrategy
    {
        private:
            data::IGame *game;
            bool running; // Actual game is running?
            data::IPlayer *lastWinner;

            void endGame();
            void convertCoords(int *y);
            // Strategy method to override
            virtual bool checkRow(int x, int y, data::IPlayer *p) = 0;
        public:
            GameControllerStrategy();
            virtual ~GameControllerStrategy();

            void playGame(data::IGame *game);
            bool isRunning();
            data::IPlayer *onTurn(); // From field
            bool toggleTurn(int x, int y); // Switches between the 2 players

            data::IPlayer *getLastWinner();
            data::IGame *getGame();
    };

}

#endif // GAMECONTROLLERSTRATEGY_H
