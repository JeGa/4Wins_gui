#include "GameFactory.h"
#include "ICell.h"
#include "impl/Cell.h"
#include "IField.h"
#include "impl/Field.h"
#include "GameControllerStrategy.h"
#include "GameControllerStandard.h"
#include "IGame.h"
#include "impl/Game.h"
#include "IPlayer.h"
#include "impl/Player.h"
#include "GameManagerLocal.h"
#include "GameManagerNetworkClient.h"
#include "GameManagerNetworkServer.h"
#include <string>

namespace controller
{

    using namespace data;

    const int GameFactory::DEFAULT_WIDTH;
    const int GameFactory::DEFAULT_HEIGHT;

    ICell ***GameFactory::initField(int w, int h)
    {
        if (w <= 0 || h <= 0)
            throw "Width and height must be > 0";

        ICell ***cell_field = new ICell**[w];

        for (int i = 0; i < w; i++) {
            cell_field[i] = new ICell*[h];
            for (int j = 0; j < h; j++) {
                cell_field[i][j] = new Cell;
            }
        }

        return cell_field;
    }

    IField *GameFactory::getField(int x, int y)
    {
        return new Field(initField(x, y), x, y);
    }

    IField *GameFactory::getDefaultField()
    {
        return new Field(initField(DEFAULT_WIDTH, DEFAULT_HEIGHT),
                         DEFAULT_WIDTH, DEFAULT_HEIGHT);
    }

    GameControllerStrategy *GameFactory::getGameController()
    {
        GameControllerStrategy *gc = new GameControllerStandard;

        return gc;
    }

    IGame *GameFactory::getGame(int x, int y, std::shared_ptr<IPlayer> p1,
        std::shared_ptr<IPlayer> p2,
        std::shared_ptr<IPlayer> turn)
    {
        IGame *game = new Game(getField(x, y), p1, p2, turn);

        return game;
    }

    IGame *GameFactory::getGameDefault(std::shared_ptr<IPlayer> p1,
        std::shared_ptr<IPlayer> p2,
        std::shared_ptr<IPlayer> turn)
    {
        IGame *game = new Game(getDefaultField(), p1, p2, turn);

        return game;
    }

    IPlayer *GameFactory::getPlayer(string name, string pw)
    {
        return new Player(name, pw);
    }

    IGameManagerLocal *GameFactory::getGameManagerLocal(IGameController *gc)
    {
        GameManagerLocal *manager = new GameManagerLocal(gc);
        return manager;
    }

    IGameManagerClient *GameFactory::getGameManagerClient()
    {
        GameManagerNetworkClient *manager = new GameManagerNetworkClient();
        return manager;
    }
    
    IGameManagerServer *GameFactory::getGameManagerServer(IGameController *gc)
    {
        GameManagerNetworkServer *manager = new GameManagerNetworkServer(gc);
        return manager;
    }

}
