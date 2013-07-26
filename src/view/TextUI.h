#ifndef TEXTUI_H
#define TEXTUI_H

#include "IPlayer.h"
#include "GameFactory.h"
#include "IGame.h"
#include "GameControllerStrategy.h"
#include "GameControllerStandard.h"
#include "IGameManager.h"
#include "IUserInterface.h"
#include <string>

#include "implTUI/TextUIElement.h"

namespace view
{
    
    using namespace controller;
    using namespace data;
    using namespace std;

    class TextUI : public IUserInterface
    {
        private:
            GameFactory factory;
            IGameManager *manager;

            void startLocalGame();
            //startNetworkGame();
            void gameLoop();
            
            // TUI elements
            tui::TuiElem mainTui;
            tui::TuiElem localGameTui;
            tui::TuiElem networkGameMainTui;
            tui::TuiElem settingsTui;
            tui::TuiElem networkGamePlayTui;
            tui::TuiElem networkGameProfileTui;
        public:
            TextUI();
            ~TextUI();
            
            virtual void run();
    };

}

#endif // TEXTUI_H
