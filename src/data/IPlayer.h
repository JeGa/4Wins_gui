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

            // For networking
            virtual void setAllData(int k, int w, int l, int p, double r,
                bool logged) = 0;
            virtual void setLoggedIn(bool l) = 0;
            // Player with statistics
            virtual void addGameStatistic(int result) = 0;
            virtual void writeToDisk() = 0;

            virtual std::string getName() = 0;
            virtual std::string getPassword() = 0;
            virtual unsigned int getKey() = 0;
            virtual int getWins() = 0;
            virtual int getLooses() = 0;
            virtual int getPlayedGames() = 0;
            virtual double getWinRatio() = 0;
            virtual bool isLoggedIn() = 0;
            virtual std::string toString() = 0;
    };

}

#endif // IPLAYER_H
