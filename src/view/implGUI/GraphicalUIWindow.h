#ifndef GRAPHICALUIWINDOW_H
#define GRAPHICALUIWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>
#include <Fl/fl_button.h>
#include <Fl/fl_wizard.h>
#include <Fl/fl_menu_bar.h>
#include <Fl/Fl_input.h>

#include "GraphicalUILocalMain.h"

namespace view { namespace gui
{

    class GraphicalUIWindow : public Fl_Window
    {
    private:
        Fl_Wizard *wizard;
        Fl_Menu_Bar *menubar;
        
        Fl_Button *btn_localGame;
        Fl_Input *p1Name;
        Fl_Input *p1Password;
        Fl_Input *p2Name;
        Fl_Input *p2Password;

        Fl_Button *btn_loginGame;
        Fl_Input *loginName;
        Fl_Input *loginPassword;
        
        Fl_Button *btn_register;
        Fl_Input *registerName;
        Fl_Input *registerPassword;
        
        GraphicalUILocalMain *localMain;
        
        // Static callbacks
        static void scb_btn_localGame(Fl_Widget *w, void *p);
        static void scb_btn_loginGame(Fl_Widget *w, void *p);
        static void scb_btn_register(Fl_Widget *w, void *p);
        
        // Callbacks
        void cb_btn_localGame();
        void cb_btn_loginGame();
        void cb_btn_register();
        
        //virtual int handle(int event) override;
    public:
        GraphicalUIWindow();
        virtual ~GraphicalUIWindow();
    };

}
}

#endif // GRAPHICALUIWINDOW_H
