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

    IGame *GameFactory::getGame(int x, int y, IPlayer *p1, IPlayer *p2, IPlayer *turn)
    {
        IGame *game = new Game(getField(x, y), p1, p2, turn);

        return game;
    }

    IGame *GameFactory::getGameDefault(IPlayer *p1, IPlayer *p2, IPlayer *turn)
    {
        IGame *game = new Game(getDefaultField(), p1, p2, turn);

        return game;
    }

    IPlayer *GameFactory::getPlayer(string name, string pw)
    {
        return new Player(name, pw);
    }

/*
    IGame *GameFactory::getGameAllNew(int x, int y, string name1, string pw1, string name2, string pw2)
    {
        IPlayer *p1 = new Player(name1, pw1);
        IPlayer *p2 = new Player(name2, pw2);

        IGame *game = new Game(getField(x, y), p1, p2, p1);

        return game;
    }
*/

}
