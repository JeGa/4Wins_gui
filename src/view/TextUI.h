#ifndef TEXTUI_H
#define TEXTUI_H

#include "IPlayer.h"
#include "GameFactory.h"
#include "IGame.h"
#include "GameControllerStrategy.h"
#include "LoginManager.h"
#include <string>

namespace view
{
    using namespace controller;
    using namespace data;
    using namespace std;

    class TextUI
    {
        private:
            GameFactory factory;
            LoginManager login;

            // Local players
            IPlayer *p1;
            IPlayer *p2;

            GameControllerStrategy *gc;
            IGame *game;

            void startLocalGame();
            //startNetworkGame();
        public:
            TextUI();
            ~TextUI();

            void menu();
            bool setInput(int x, int y); // Call from game loop
            string toString();
    };

}

#endif // TEXTUI_H
