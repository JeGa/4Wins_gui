/*
* The implGUI package builds the gui. All events are handled in
* this class. 
*/

#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include "IPlayer.h"
#include "GameFactory.h"
#include "IGame.h"
#include "GameControllerStrategy.h"
#include "LoginManager.h"
#include "IUserInterface.h"
#include "GraphicalUIWindow.h"

namespace view { namespace gui {
    class GraphicalUIWindow;
}}

namespace view
{

    class GraphicalUI : public IUserInterface
    {
    private:
        controller::GameFactory factory;
        controller::IGameManager *manager;
        
        void startLocalGame();
        //void startNetworkGame();
        
        // GUI
        gui::GraphicalUIWindow *window;
        
        // Static callbacks
        static void scb_btn_localGame(Fl_Widget *w, void *p);
        static void scb_btn_loginGame(Fl_Widget *w, void *p);
        static void scb_btn_register(Fl_Widget *w, void *p);
        static void scb_field(Fl_Widget *w, void *p);
        
        // Callbacks
        void cb_btn_localGame();
        void cb_btn_loginGame();
        void cb_btn_register();
        void cb_field();

    public:
        GraphicalUI();
        ~GraphicalUI();
        
        virtual void run();
    };

}

#endif // GRAPHICALUI_H
