/*
* Override for different implementations.
* All classes use interfaces!
*/

#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "ICell.h"
#include "IField.h"
#include "IGame.h"
#include "IPlayer.h"
#include "GameControllerStrategy.h"
#include "IGameManager.h"

#include <string>

namespace controller
{

    using namespace data;
    using namespace std;

    class GameFactory
    {
        private:
            ICell ***initField(int x, int y);

        public:
            static const int DEFAULT_WIDTH = 5;
            static const int DEFAULT_HEIGHT = 8;

            virtual IField *getField(int x, int y);
            virtual IField *getDefaultField();
            virtual GameControllerStrategy *getGameController();
            virtual IPlayer *getPlayer(string name, string pw);
            // Given size
            virtual IGame *getGame(int x, int y, IPlayer *p1, IPlayer *p2, IPlayer *turn);
            // Default size
            virtual IGame *getGameDefault(IPlayer *p1, IPlayer *p2, IPlayer *turn);
            // Creates new game with new players
            //virtual IGame *getGameAllNew(int x, int y, string name1, string pw1, string name2, string pw2);
            virtual IGameManager *getGameManagerLocal(IGameController *gc);
    };

}

#endif // GAMEFACTORY_H
