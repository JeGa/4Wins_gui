#include "TextUI.h"

#include "GameFactory.h"
#include "IGame.h"
#include "GameControllerStrategy.h"
#include <string>
#include <iostream>

namespace view
{

    using namespace controller;
    using namespace data;
    using namespace std;

    TextUI::TextUI() : mainTui(40, 6)
    {        
        // Set TUI elements
        mainTui.setLabel("4Wins_gui");
        mainTui.setText("4Wins: Text User Interface");
        
        localGameTui.setLabel("1) Local Game");
        localGameTui.setText("Local Game Text");
        
        settingsTui.setLabel("3) Settings");
        
        networkGameMainTui.setLabel("2) Network Game");
        networkGameMainTui.setText("Login sucessfull.");
        
        networkGamePlayTui.setLabel("1) Play network game");
        networkGameProfileTui.setLabel("2) View player profiles");
        
        mainTui.addChild(&localGameTui);
        mainTui.addChild(&networkGameMainTui);
        mainTui.addChild(&settingsTui);
        
        networkGameMainTui.addChild(&networkGamePlayTui);
        networkGameMainTui.addChild(&networkGameProfileTui);
        
       // manager = factory.getGameManagerLocal(factory.getGameController());
    }

    TextUI::~TextUI()
    {
        delete manager;
    }

    void TextUI::startLocalGame()
    {
        string p1_name, p2_name;
        int w, h;

        cout << "Set up:" << endl;

        cout << "Width and height: ";
        cin >> w;
        cin >> h;
        cout << "Player1 name: ";
        cin >> p1_name;
        cout << "Player2 name: ";
        cin >> p2_name;
        
        //IPlayer *p1 = factory.getPlayer(p1_name, "local");
        //IPlayer *p2 = factory.getPlayer(p2_name, "local");
        //IGame *game = factory.getGame(w, h, p1, p2, p1);

        //manager->newGame(game);
        
        //gameLoop();

        // GameManager is responsible for freeing the memory!
    }
    
    // Menu input
    void TextUI::run()
    {
        while (true) {
            // Display TUI
            std::cout << std::endl;
            mainTui.display();
            tui::TuiElem *choice = mainTui.ask();
            std::cout << std::endl;
            
            if (choice == &this->localGameTui) {
                startLocalGame();
            }
        }
    }
    
    // Game input
    void TextUI::gameLoop()
    {/*
        while (manager->getActiveGame()->isRunning()) {
            cout << endl << manager->getActiveGame()->toString() << endl;
            cout << manager->getActiveGame()->onTurn()->getName() << " -> X and Y coordinates: ";
            
            int x, y;
            cin >> x;
            cin >> y;
            
            manager->input(x, y);
        }
        cout << endl << "== WINNER IS: " <<
            manager->getActiveGame()->getWinner()->getName() << "! ==" << endl;*/
    }

}
