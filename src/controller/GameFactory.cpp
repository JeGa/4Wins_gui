#include "GameFactory.h"
#include "Cell.h"
#include "Field.h"
#include "Game.h"
#include "Player.h"
#include "GameControllerStandard.h"

namespace controller
{

    const int GameFactory::DEFAULT_WIDTH;
    const int GameFactory::DEFAULT_HEIGHT;

    data::ICell ***GameFactory::initField(int w, int h)
    {
        if (w <= 0 || h <= 0)
            throw "Width and height must be > 0";

        data::ICell ***cell_field = new data::ICell**[w];

        for (int i = 0; i < w; i++) {
            cell_field[i] = new data::ICell*[h];
            for (int j = 0; j < h; j++) {
                cell_field[i][j] = new data::Cell;
            }
        }

        return cell_field;
    }

    data::IField *GameFactory::getField(int x, int y)
    {
        return new data::Field(initField(x, y), x, y);
    }

    data::IField *GameFactory::getDefaultField()
    {
        return new data::Field(initField(DEFAULT_WIDTH, DEFAULT_HEIGHT),
                         DEFAULT_WIDTH, DEFAULT_HEIGHT);
    }

    // TODO
    GameControllerStrategy *GameFactory::getGameController()
    {
        GameControllerStrategy *gc = new GameControllerStandard;

        return gc;
    }

    std::shared_ptr<data::IGame> GameFactory::getGame(int x, int y,
        std::shared_ptr<data::IPlayer> p1,
        std::shared_ptr<data::IPlayer> p2,
        std::shared_ptr<data::IPlayer> turn)
    {
        return std::make_shared<data::Game>(getField(x, y), p1, p2, turn);
    }

    std::shared_ptr<data::IGame> GameFactory::getGameDefault(
        std::shared_ptr<data::IPlayer> p1,
        std::shared_ptr<data::IPlayer> p2,
        std::shared_ptr<data::IPlayer> turn)
    {
        return std::make_shared<data::Game>(getDefaultField(), p1, p2, turn);
    }

    std::shared_ptr<data::IPlayer> GameFactory::getPlayer(std::string name, std::string pw)
    {
        return std::make_shared<data::Player>(name, pw);
    }

}
