/*
* LoginManager manages all players (including memory)
* and all games (including memory).
*/

#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "IPlayer.h"
#include "IGame.h"
#include <vector>

namespace controller
{

    using namespace std;
    using namespace data;

    class LoginManager
    {
        private:
            vector<IPlayer*> players;
            vector<IGame *> games;

            void readPlayersFromDisk(vector<IPlayer*> *players);
        public:
            LoginManager();
            ~LoginManager();
            IPlayer *createNewUser(string name, string pw);
            IPlayer *logIn(string name, string pw); // Checks if player exists ...
            bool logOut(IPlayer *player); // Saves player to disk
    };

}

#endif // LOGINMANAGER_H
