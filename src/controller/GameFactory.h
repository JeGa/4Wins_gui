/*
* Override for different implementations. All classes use interfaces!
*
* TODO: Return smart pointers instead of raw pointers.
* TODO: The manager stuff.
*/

/*
    std::unique_ptr<IGameManagerLocal> GameFactory::getGameManagerLocal()
    {
        return std::unique_ptr<IGameManagerLocal> p(new GameManagerLocal(););
    }

    std::unique_ptr<IGameManagerClient> GameFactory::getGameManagerClient()
    {
        return std::unique_ptr<IGameManagerClient>(new GameManagerNetworkClient());
    }

    std::unique_ptr<IGameManagerServer> GameFactory::getGameManagerServer(IGameController *gc)
    {
        return std::unique_ptr<IGameManagerServer>(new GameManagerNetworkServer(gc));
    }
*/

#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "ICell.h"
#include "IField.h"
#include "IGame.h"
#include "IPlayer.h"
#include "GameControllerStrategy.h"
#include <string>
#include <memory>

namespace controller
{

    class GameFactory
    {
        private:
            data::ICell ***initField(int x, int y);

        public:
            static const int DEFAULT_WIDTH = 5;
            static const int DEFAULT_HEIGHT = 8;

            virtual data::IField *getField(int x, int y);
            virtual data::IField *getDefaultField();

            virtual std::shared_ptr<data::IPlayer> getPlayer(std::string name, std::string pw);
            // Given size
            virtual std::shared_ptr<data::IGame> getGame(int x, int y,
                std::shared_ptr<data::IPlayer> p1,
                std::shared_ptr<data::IPlayer> p2,
                std::shared_ptr<data::IPlayer> turn);
            // Default size
            virtual std::shared_ptr<data::IGame> getGameDefault(
                std::shared_ptr<data::IPlayer> p1,
                std::shared_ptr<data::IPlayer> p2,
                std::shared_ptr<data::IPlayer> turn);

            virtual GameControllerStrategy *getGameController();
    };

}

#endif // GAMEFACTORY_H
