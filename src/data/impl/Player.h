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

            // For key generation
            static int playerCounter;
            size_t key;

            // Statistics
            int wins;
            int looses;
            int playedGames;
            double winRatio;
            
            // Networking
            bool loggedIn = false;
        public:
            Player(std::string name, std::string pw);
            virtual ~Player();

            virtual void setAllData(int k, int w, int l, int p, double r, bool logged);
            virtual void writeToDisk();
            virtual void addGameStatistic(int result);
            virtual void setLoggedIn(bool l);

            virtual unsigned int getKey();
            virtual std::string getName();
            virtual std::string getPassword();
            virtual int getWins();
            virtual int getLooses();
            virtual int getPlayedGames();
            virtual double getWinRatio();
            virtual bool isLoggedIn();
            virtual std::string toString();
    };

}

#endif // PLAYER_H
