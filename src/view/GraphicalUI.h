#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include "IPlayer.h"
#include "GameFactory.h"
#include "IGame.h"
#include "GameControllerStrategy.h"
#include "LoginManager.h"
#include "IUserInterface.h"
#include "GraphicalUIWindow.h"

namespace view
{
    
    using namespace controller;
    using namespace data;

    class GraphicalUI : public IUserInterface
    {
    private:
        GameFactory factory;
        IGameManager *manager;
        
        void startLocalGame();
        //void startSettingsWindow();
        
        // GUI
        gui::GraphicalUIWindow window;
        
        // Callbacks
        /*static void scb_window(Fl_Widget *w, void *p);
        void cb_window(Fl_Widget *w);*/
    public:
        GraphicalUI();
        ~GraphicalUI();
        
        virtual void run();
    };

}

#endif // GRAPHICALUI_H
