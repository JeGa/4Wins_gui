#ifndef PLAYER_H
#define PLAYER_H

#include "IPlayer.h"
#include <string>
#include <vector>

namespace data
{

    class Player : public IPlayer
    {
        private:
            std::string name;
            std::string password;
            //std::vector<Game> games;

            // For key generation
            static int playerCounter;
            size_t key;

            // Statistics
            int wins;
            int looses;
            int playedGames;
            double winRatio;
        public:
            Player(std::string name, std::string pw);
            virtual ~Player();
            virtual std::string getName();
            virtual std::string getPassword();
            virtual void writeToDisk();
            //virtual bool verifypassword(std::string pw);
            virtual std::string toString();
            
            virtual int getKey();

            // Player with statistics
            virtual void addGameStatistic(int result);
            virtual int getWins();
            virtual int getLooses();
            virtual int getPlayedGames();
            virtual double getWinRatio();
    };

}

#endif // PLAYER_H
