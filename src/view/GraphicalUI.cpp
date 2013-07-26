/*
* The other GUI classes are only responsible for displaying. The game
* is controlled in this class. Only the following classes have
* access to the game (only read data):
* 
* - GUI: Game/Field needs game object to display the game field.
*/

#include "GraphicalUI.h"
#include "IPlayer.h"
#include "GraphicalUIGame.h"

#include "NetworkControllerClient.h"
#include "NetworkControllerServer.h"

namespace view
{
    
    GraphicalUI::GraphicalUI()
    {
        // The main window
        window = new gui::GraphicalUIWindow();
        
        // Menu callbacks
        window->menu->btn_localGame->callback(scb_btn_localGame, this);
        window->menu->btn_loginGame->callback(scb_btn_loginGame, this);
        window->menu->btn_register->callback(scb_btn_register, this);
        
        // Status callbacks
        window->status->btn_logout->callback(scb_btn_logout, this); //!! Put in status class
        
        //!! TODO: Check server status
//        if (client.ping()) {
//            window->status->connectionStatusText->color(FL_GREEN);
//            window->status->redraw();
//        }
    }

    GraphicalUI::~GraphicalUI()
    {
        delete window;
        if (manager != nullptr)
            delete manager;
        if (managerServer != nullptr)
            delete managerServer;
    }
    
    // Main loop for window
    void GraphicalUI::run()
    {
        window->show();
        while(Fl::wait());
    }
    
    void GraphicalUI::startNetworkGame()
    {
        if (manager != nullptr)
            delete manager;
            
        manager = factory.getGameManagerNetwork();
    }
    
    void GraphicalUI::startLocalGame()
    {
        if (manager != nullptr)
            delete manager;
            
        manager = factory.getGameManagerLocal(factory.getGameController());
            
        const char *p1Name = window->menu->p1Name->value();
        const char *p2Name = window->menu->p2Name->value();
        
        data::IPlayer *p1 = nullptr;
        data::IPlayer *p2 = nullptr;
        
        if (manager->getActiveGame() == nullptr) {
            p1 = factory.getPlayer(p1Name, "");
            p2 = factory.getPlayer(p2Name, "");
        } else {
            p1 = manager->getActiveGame()->getPlayer1();
            p2 = manager->getActiveGame()->getPlayer2();
        
            // If the name is the same, use the old player
            // else create new player.
            if (p1->getName().compare(p1Name))
                p1 = factory.getPlayer(p1Name, "");
            if (p2->getName().compare(p2Name))
                p2 = factory.getPlayer(p2Name, "");
        }
    
        // Sets the new game
        manager->newGame(factory.getGame(window->menu->hor->value(),
            window->menu->vert->value(), p1, p2, p1));
        
        // GUI for one game
        gui::GraphicalUIGame *game = new gui::GraphicalUIGame();
        
        game->callback(scb_game, this);
        game->displayGame(manager->getActiveGame());
        game->show();
    }
    
    // Callbacks =====================================================
    
    void GraphicalUI::scb_btn_localGame(Fl_Widget *w, void *p)
    {
        (static_cast<GraphicalUI *>(p))->cb_btn_localGame();
    }
    
    void GraphicalUI::cb_btn_localGame()
    {
        // TODO: Validate input
        
        startLocalGame();
    }
    
    void GraphicalUI::scb_btn_loginGame(Fl_Widget *w, void *p)
    {
        (static_cast<GraphicalUI *>(p))->cb_btn_loginGame();
    }
    
    void GraphicalUI::cb_btn_loginGame()
    {
        // Switch to tab group
        window->menu->hide();
        window->html->hide();
        window->tabs->show();
    }
    
    void GraphicalUI::scb_btn_register(Fl_Widget *w, void *p)
    {
        (static_cast<GraphicalUI *>(p))->cb_btn_register();
    }
    
    void GraphicalUI::cb_btn_register()
    {
        //registerPlayer();
    }
    
    void GraphicalUI::scb_game(Fl_Widget *w, void *p)
    {
        (static_cast<GraphicalUI *>(p))->cb_game(w);
    }
    
    //!! TODO: Put this in the manager class
    
    // Field is clicked
    void GraphicalUI::cb_game(Fl_Widget *w)
    {
        gui::GraphicalUIGame *game = static_cast<gui::GraphicalUIGame *>(w);
        
        // If the window is closed: Delete the game from the manager
        if (Fl::event() == FL_CLOSE) {
            manager->deleteGame(game->game);
            game->hide();
            return;
        }
        
        // Get clicked cell
        gui::CellDrawing *cell = game->field->getClickedCell();
        
        // Set the active game for the manager
        if (!manager->setActiveGame(game->game))
            return;
        
        // Only make turn if the game is running
        if (manager->getActiveGame()->isRunning()) {
            manager->input(cell->xNr, cell->yNr);
            game->setInfoOutput();
        }
        
        if (!manager->getActiveGame()->isRunning()) {
            data::IPlayer *winner = manager->getActiveGame()->getWinner();
            
            game->setWinnerOutput(winner);
        }
        
        game->field->redraw();
    }
    
    void GraphicalUI::scb_btn_logout(Fl_Widget *w, void *p)
    {
        (static_cast<GraphicalUI *>(p))->cb_btn_logout();
    }
    
    void GraphicalUI::cb_btn_logout()
    {
        // TODO: Logout first
        
        // Switch to start screen
        window->tabs->hide();
        //window->btn_logout->hide();
        window->menu->show();
        window->html->show();
    }

}

