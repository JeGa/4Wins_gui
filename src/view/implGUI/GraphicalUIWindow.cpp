#include "GraphicalUIWindow.h"

//!!
#include "GraphicalUIField.h"

namespace view { namespace gui
{

    GraphicalUIWindow::GraphicalUIWindow() :
        Fl_Window(800, 600, "4Wins_gui")
    {
        menubar = new Fl_Menu_Bar(0, 0, w(), 25);
        menubar->add("&File/&Open", 0, 0, 0, FL_MENU_DIVIDER);
        //menubar->add("&File/&Quit", 0, scb_menubar, (void *)this);
        menubar->add("&Settings/&Test", 0, 0);
        menubar->add("&Whatever/&Test", 0, 0);
        
        wizard = new Fl_Wizard(0, menubar->h(),
            w(), h() - menubar->h());
        
        // Child 1 - Main window
        Fl_Group *g1 = new Fl_Group(wizard->x(), wizard->y(),
            wizard->w(), wizard->h());
            
            btn_localGame = new Fl_Button(50, 50, 100, 25, "Local");
            btn_localGame->callback(scb_btn_localGame, this);
            p1Name = new Fl_Input(200, 50, 100, 25);
            p1Password = new Fl_Input(320, 50, 100, 25);
            p2Name = new Fl_Input(500, 50, 100, 25);
            p2Password = new Fl_Input(620, 50, 100, 25);
            
            btn_loginGame = new Fl_Button(50, 100, 100, 25, "Login");
            loginName = new Fl_Input(200, 100, 100, 25);
            loginPassword = new Fl_Input(320, 100, 100, 25);
            
            btn_register = new Fl_Button(50, 150, 100, 25, "Register");
            registerName = new Fl_Input(200, 150, 100, 25);
            registerPassword = new Fl_Input(320, 150, 100, 25);
            
            GraphicalUIField *a = new GraphicalUIField();
            
        g1->end();
        
        // Child 2 - Local
        Fl_Group *g2 = new Fl_Group(wizard->x(), wizard->y(),
            wizard->w(), wizard->h());
        
        localMain = new GraphicalUILocalMain();
        
        g2->end();
        
        // Child 3 - Network
        Fl_Group *g3 = new Fl_Group(wizard->x(), wizard->y(),
            wizard->w(), wizard->h());
            
            //!!
        
        g3->end();
        
        wizard->end(); 
        
        end();
        
        this->modal();
    }

    GraphicalUIWindow::~GraphicalUIWindow()
    {
    }
    
    void GraphicalUIWindow::scb_btn_localGame(Fl_Widget *w, void *p)
    {
        ((GraphicalUIWindow *) p)->cb_btn_localGame();
    }
    
    void GraphicalUIWindow::cb_btn_localGame()
    {
        wizard->next();
    }
    
    void GraphicalUIWindow::scb_btn_loginGame(Fl_Widget *w, void *p)
    {
        ((GraphicalUIWindow *) p)->cb_btn_localGame();
    }
    
    void GraphicalUIWindow::cb_btn_loginGame()
    {
        wizard->next();
    }
    
    void GraphicalUIWindow::scb_btn_register(Fl_Widget *w, void *p)
    {
        ((GraphicalUIWindow *) p)->cb_btn_localGame();
    }
    
    void GraphicalUIWindow::cb_btn_register()
    {
        wizard->next();
    }
    
/*    int GraphicalUIWindow::handle(int event)
    {
        return Fl_Window::handle(event);
    }*/

}
}

