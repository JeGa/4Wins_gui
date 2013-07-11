#include "GraphicalUI.h"
#include "IPlayer.h"

namespace view
{
    
    GraphicalUI::GraphicalUI()
    {
        manager = factory.getGameManagerLocal(factory.getGameController());

        window = new gui::GraphicalUIWindow();
        
        // Add callbacks
        window->menu->btn_localGame->callback(scb_btn_localGame, this);
        window->menu->btn_loginGame->callback(scb_btn_loginGame, this);
        window->menu->btn_register->callback(scb_btn_register, this);
        
        window->field->callback(scb_field, this);
        this->window->field->setGameManager(manager);
    }

    GraphicalUI::~GraphicalUI()
    {
        delete window;
        delete manager;
    }
    
    void GraphicalUI::startLocalGame()
    {
        const char *p1Name = window->menu->p1Name->value();
        const char *p2Name = window->menu->p2Name->value();
        const char *p1Pw = window->menu->p1Password->value();
        const char *p2Pw = window->menu->p2Password->value();
        
        //!! TODO: ID for player
        data::IPlayer *p1 = this->factory.getPlayer(p1Name, p1Pw);
        data::IPlayer *p2 = this->factory.getPlayer(p2Name, p2Pw);
        
        this->manager->newGame(this->factory.getGameDefault(p1, p2, p1));
        
        this->window->field->displayGame();
        //this->window->field->redraw();
    }
    
    void GraphicalUI::run()
    {
        window->show();
        while(Fl::wait());
    }
    
    // Callbacks =====================================================
    
    void GraphicalUI::scb_btn_localGame(Fl_Widget *w, void *p)
    {
        ((GraphicalUI *) p)->cb_btn_localGame();
    }
    
    void GraphicalUI::cb_btn_localGame()
    {
        startLocalGame();
    }
    
    void GraphicalUI::scb_btn_loginGame(Fl_Widget *w, void *p)
    {
        ((GraphicalUI *) p)->cb_btn_localGame();
    }
    
    void GraphicalUI::cb_btn_loginGame()
    {
        //startNetworkgame();
    }
    
    void GraphicalUI::scb_btn_register(Fl_Widget *w, void *p)
    {
        ((GraphicalUI *) p)->cb_btn_localGame();
    }
    
    void GraphicalUI::cb_btn_register()
    {
        //registerPlayer();
    }
    
    void GraphicalUI::scb_field(Fl_Widget *w, void *p)
    {
        ((GraphicalUI *) p)->cb_field();
    }
    
    // Field input.
    void GraphicalUI::cb_field()
    {
        // Get clicked cell
        gui::CellDrawing *cell = window->field->getClickedCell();
        
        // Cell is clicked
        if (manager->getGameController()->isRunning())
            manager->getGameController()->toggleTurn(cell->xNr, cell->yNr);
            
        if (!manager->getGameController()->isRunning())
            data::IPlayer *winner = manager->getGameController()->getLastWinner();
        else
            data::IPlayer *onTurn = manager->getGameController()->onTurn();
            
        window->field->redraw();
    }

}