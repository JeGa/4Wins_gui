/*
* Up from this class IPlayer and its key is uesd to identify players.
* The enum Colors is only used internal.
*
* A game manages the field and the two players. It can live completely alone.
* A shared pointer is used because a game owns the player, too.
*/

#ifndef GAME_H
#define GAME_H

#include "IGame.h"
#include "IField.h"
#include <string>
#include <memory>

namespace data
{

    class Game : public IGame
    {
        private:
            bool running;

            // For key generation
            static int gameCounter;
            size_t key;

            std::unique_ptr<IField> field;

            std::shared_ptr<IPlayer> player1;
            std::shared_ptr<IPlayer> player2;
            std::shared_ptr<IPlayer> winner;

            std::shared_ptr<IPlayer> turn;
        public:
            Game(IField *field,
                std::shared_ptr<IPlayer> player1,
                std::shared_ptr<IPlayer> player2,
                std::shared_ptr<IPlayer> onTurn);
            virtual ~Game() {}

            virtual void setRunning(bool running);
            virtual void setWinner(size_t keyWinner);
            virtual void setCellStatus(int x, int y, std::shared_ptr<IPlayer> player);

            virtual std::shared_ptr<IPlayer> onTurn();
            virtual std::shared_ptr<IPlayer> notOnTurn();
            virtual std::shared_ptr<IPlayer> getCellStatus(int x, int y);
            virtual std::shared_ptr<IPlayer> getWinner();
            virtual std::shared_ptr<IPlayer> getPlayer1();
            virtual std::shared_ptr<IPlayer> getPlayer2();
            virtual bool isRunning();
            virtual int getWidth();
            virtual int getHeight();
            virtual int getKey();
            virtual std::string toString();

            Game& operator=(Game& other) = delete;
            Game(Game& other) = delete;
    };

}

#endif // GAME_H
