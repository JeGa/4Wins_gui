#ifndef IGAME_H
#define IGAME_H

#include "IPlayer.h"
#include <string>
#include <memory>

namespace data
{

    class IGame
    {
        public:
            virtual ~IGame() {}

            virtual void setRunning(bool running) = 0;
            virtual void setWinner(size_t keyWinner) = 0;
            // Wrapper for field
            virtual void setCellStatus(int x, int y, size_t key) = 0;

            virtual bool isRunning() = 0;
            virtual std::shared_ptr<IPlayer> getPlayer1() = 0;
            virtual std::shared_ptr<IPlayer> getPlayer2() = 0;
            virtual std::shared_ptr<IPlayer> getWinner() = 0;
            virtual std::shared_ptr<IPlayer> onTurn() = 0;
            virtual std::shared_ptr<IPlayer> notOnTurn() = 0;
            // Wrapper for field
            virtual std::shared_ptr<IPlayer> getCellStatus(int x, int y) = 0;
            virtual int getWidth() = 0;
            virtual int getHeight() = 0;
            virtual int getKey() = 0;
            virtual std::string toString() = 0;
    };

}

#endif // IGAME_H
