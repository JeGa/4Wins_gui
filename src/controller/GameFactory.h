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
#include "IGameManagerLocal.h"
#include "IGameManagerClient.h"
#include "IGameManagerServer.h"
#include <string>
#include <memory>

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

            virtual std::shared_ptr<data::IPlayer> getPlayer(string name, string pw);
            // TODO: Game nor raw pointer
            // Given size
            virtual IGame *getGame(int x, int y,
                std::shared_ptr<data::IPlayer> p1,
                std::shared_ptr<data::IPlayer> p2,
                std::shared_ptr<data::IPlayer> turn);
            // Default size
            virtual IGame *getGameDefault(
                std::shared_ptr<data::IPlayer> p1,
                std::shared_ptr<data::IPlayer> p2,
                std::shared_ptr<data::IPlayer> turn);

            virtual GameControllerStrategy *getGameController();
            virtual IGameManagerLocal *getGameManagerLocal(IGameController *gc);
            virtual IGameManagerClient *getGameManagerClient();
            virtual IGameManagerServer *getGameManagerServer(IGameController *gc);
    };

}

#endif // GAMEFACTORY_H
