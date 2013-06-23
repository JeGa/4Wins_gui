#include "Game.h"

#include "IGame.h"
#include "IField.h"
#include <string>

namespace data
{

    Game::Game(IField *field, IPlayer *player1, IPlayer *player2, IPlayer *turn)
        : field(field), player1(player1), player2(player2), turn(turn)
    {

    }

    Game::~Game()
    {
        delete field;
    }

    IPlayer *Game::onTurn()
    {
        return turn;
    }

    IPlayer *Game::notOnTurn()
    {
        if (turn == player1)
            return player2;
        return player1;
    }

    void Game::setCellStatus(int x, int y, IPlayer *player)
    {
        if (player == player1) {
            field->setCellStatus(x, y, PLAYER1);
            turn = player2;
        } else if (player == player2) {
            field->setCellStatus(x, y, PLAYER2);
            turn = player1;
        } else
            throw "Player doesnt play this game";
    }

    IPlayer *Game::getCellStatus(int x, int y)
    {
        Colors c = field->getCellStatus(x, y);
        if (c == PLAYER1)
            return player1;
        if (c == PLAYER2)
            return player2;
        return NULL;
    }

    IPlayer *Game::getPlayer1()
    {
        return player1;
    }

    IPlayer *Game::getPlayer2()
    {
        return player2;
    }

    int Game::getWidth()
    {
        return field->getWidth();
    }

    int Game::getHeight()
    {
        return field->getHeight();
    }

    std::string Game::toString()
    {
        std::string str;
        str += player1->toString();
        str += player2->toString();
        str += "OnTurn: " + turn->getName() + '\n';
        str += field->toString();
        return str;
    }

}
