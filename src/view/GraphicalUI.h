#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include "IPlayer.h"
#include "GameFactory.h"
#include "IGame.h"
#include "GameControllerStrategy.h"
#include "LoginManager.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Wizard.H>

namespace view
{
    using namespace controller;
    using namespace data;

    class GraphicalUI : public Fl_Window
    {
        private:
            GameFactory factory;
            LoginManager login;

            // Local players
            IPlayer *p1;
            IPlayer *p2;

            GameControllerStrategy *gc;
            IGame *game;


            Fl_Button *btn_localGame;
            Fl_Menu_Bar *menubar;
            Fl_Wizard *wizard;

            void startLocalGame();
            void startSettingsWindow();
        public:
            GraphicalUI();
            ~GraphicalUI();
            void start();
            //void cb_menubar(Fl_Widget *w);
    };

}

#endif // GRAPHICALUI_H
