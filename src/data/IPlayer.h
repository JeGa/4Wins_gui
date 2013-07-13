#ifndef IPLAYER_H
#define IPLAYER_H

//#include "IGame.h"
#include <vector>
#include <string>

namespace data
{

    class IPlayer
    {
        public:
            static const int LOOSE = 0;
            static const int WIN = 1;

            virtual ~IPlayer() {}
            virtual void writeToDisk() = 0;
            //virtual std::vector<IGame> getGames() = 0;
            virtual std::string getName() = 0;
            //virtual bool verifypassword(std::string pw) = 0;
            virtual std::string toString() = 0;

            virtual int getKey() = 0;
            
            virtual void addGameStatistic(int result) = 0;
            virtual int getWins() = 0;
            virtual int getLooses() = 0;
            virtual int getPlayedGames() = 0;
            virtual double getWinRatio() = 0;
    };

}

#endif // IPLAYER_H
