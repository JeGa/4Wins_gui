#include "Game.h"

#include "IGame.h"
#include "IField.h"
#include <string>
#include <sstream>

namespace data
{

    int Game::gameCounter = 0;

    Game::Game(IField *field,
        std::shared_ptr<IPlayer> player1,
        std::shared_ptr<IPlayer> player2,
        std::shared_ptr<IPlayer> onTurn)
            : running(true), field(field),
            player1(player1), player2(player2),
            turn(turn), winner(nullptr)
    {
        std::stringstream stream;
        stream << this->getPlayer1()->getName() << this->getPlayer2()->getName()
               << Game::gameCounter;

        std::hash<std::string> str_hash;
        key = str_hash(stream.str());

        ++gameCounter;
    }

    std::shared_ptr<IPlayer> Game::onTurn()
    {
        return turn;
    }

    std::shared_ptr<IPlayer> Game::notOnTurn()
    {
        if (turn == player1)
            return player2;
        return player1;
    }

    void Game::setCellStatus(int x, int y, std::shared_ptr<IPlayer> player)
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

    std::shared_ptr<IPlayer> Game::getCellStatus(int x, int y)
    {
        Colors c = field->getCellStatus(x, y);
        if (c == PLAYER1)
            return player1;
        if (c == PLAYER2)
            return player2;
        return NULL;
    }

    bool Game::isRunning()
    {
        return running;
    }

    void Game::setRunning(bool running)
    {
        this->running = running;
    }

    std::shared_ptr<IPlayer> Game::getWinner()
    {
        return winner;
    }

    void Game::setWinner(size_t keyWinner)
    {
        if (player1->getKey() == keyWinner)
            winner = player1;
        else if (player2->getKey() == keyWinner)
            winner = player2;
    }

    std::shared_ptr<IPlayer> Game::getPlayer1()
    {
        return player1;
    }

    std::shared_ptr<IPlayer> Game::getPlayer2()
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

    int Game::getKey()
    {
        return key;
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
