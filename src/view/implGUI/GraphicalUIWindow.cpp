#include "GraphicalUIWindow.h"
#include "GraphicalUIField.h"

namespace view { namespace gui
{
    
    // The main window

    GraphicalUIWindow::GraphicalUIWindow() : Fl_Window(800, 600, "4Wins_gui")
    {
        menubar = new MenuBar(w(), 30);
        
        menu = new Menu(10, 40);
        menu->end();
        
        field = new GraphicalUIField(10, 250);
        
        end();
    }

    GraphicalUIWindow::~GraphicalUIWindow()
    {
    }
    
    // ===============================================================
    
    // The additional classes
    
    Menu::Menu(int x_, int y_) : Fl_Group(x_, y_, 0, 0)
    { 
        int sizeX = 100, sizeY = 25;
        int offsetX = 10, offsetY = 10;
        
        int startX = x_ + offsetX;
        int startY = y_ + offsetY;
        
        this->resize(x(), y(), startX + 720, startY + 80);
        box(FL_UP_BOX);
        
        btn_localGame = new Fl_Button(startX, startY, sizeX, sizeY, "Local");
        
//        Fl_Label *l1 = new Fl_Label();

        p1Name = new Fl_Input(startX + 180, startY, sizeX, sizeY);
        p1Password = new Fl_Secret_Input(startX + 290, startY, sizeX, sizeY);
        p2Name = new Fl_Input(startX + 500, startY, sizeX, sizeY);
        p2Password = new Fl_Secret_Input(startX + 610, startY, sizeX, sizeY);
        
        btn_loginGame = new Fl_Button(startX, startY + 40, sizeX, sizeY, "Login");
        loginName = new Fl_Input(startX + 180, startY + 40, sizeX, sizeY);
        loginPassword = new Fl_Secret_Input(startX + 290, startY + 40, sizeX, sizeY);
        
        btn_register = new Fl_Button(startX, startY + 80, sizeX, sizeY, "Register");
        registerName = new Fl_Input(startX + 180, startY + 80, sizeX, sizeY);
        registerPassword = new Fl_Secret_Input(startX + 290, startY + 80, sizeX, sizeY);
    };
    
    MenuBar::MenuBar(int w, int h) : Fl_Menu_Bar(0, 0, w, h)
    {
        add("&File/&Open", 0, 0, 0, FL_MENU_DIVIDER);
        add("&File/&Quit", 0, 0);
        //add("&File/&Quit", 0, scb_menubar, (void *)this);
        
        add("&View/&My Profile", 0, 0);
        
        add("&Settings/&Settings", 0, 0);
        
        add("&Help/&About", 0, 0);
    };

}
}