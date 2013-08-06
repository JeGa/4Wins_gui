#include "GraphicalUIWindow.h"
#include "GraphicalUIField.h"

namespace view { namespace gui
{
    
    // The main window

    GraphicalUIWindow::GraphicalUIWindow() : Fl_Window(800, 600, "4Wins_gui")
    {
        menubar = new MenuBar(w(), 30);
        menu = new Menu(10, 40);
        status = new StatusBar(10, 490);
        tabs = new GraphicalUITab(10, 40, this->w() - 20, 440);
        
        html = new Fl_Help_View(10, 50 + menu->h(),
            this->w() - 20, 300);

        html->load("news.html");
        html->end();
        
        end();
        
        Fl::scheme("gtk+");
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
        
        this->resize(x(), y(), this->parent()->w() - 20, startY + 80);
        box(FL_UP_BOX);
        
        btn_localGame = new Fl_Button(startX, startY, sizeX, sizeY, "Local");
        p1Name = new Fl_Input(startX + 180, startY, sizeX, sizeY);
        p1Name->label("Player 1: ");
        p2Name = new Fl_Input(startX + 380, startY, sizeX, sizeY);
        p2Name->label("Player 2: ");
        
        btn_loginGame = new Fl_Button(startX, startY + 40, sizeX, sizeY, "Login");
        loginName = new Fl_Input(startX + 180, startY + 40, sizeX, sizeY);
        loginName->label("Name: ");
        loginPassword = new Fl_Secret_Input(startX + 380, startY + 40, sizeX, sizeY);
        loginPassword->label("Password: ");
        
        btn_register = new Fl_Button(startX, startY + 80, sizeX, sizeY, "Register");
        registerName = new Fl_Input(startX + 180, startY + 80, sizeX, sizeY);
        registerName->label("Name: ");
        registerPassword = new Fl_Secret_Input(startX + 380, startY + 80, sizeX, sizeY);
        registerPassword->label("Password: ");
    
        hor = new Fl_Value_Slider(startX + 500, startY, sizeX + 20, sizeY);
        hor->bounds(4, 50);
        hor->type(FL_HOR_NICE_SLIDER);
        hor->step(1.0);
        hor->value(10);
        vert = new Fl_Value_Slider(startX + 630, startY, sizeX + 20, sizeY);
        vert->bounds(4, 30);
        vert->type(FL_HOR_NICE_SLIDER);
        vert->step(1.0);
        vert->value(16);
    
        end();
    };
    
    MenuBar::MenuBar(int w, int h) : Fl_Menu_Bar(0, 0, w, h)
    {
        add("&File/&Open Server", 0, 0, 0, FL_MENU_DIVIDER);
        add("&File/&Quit", 0, 0);
        
        add("&View/&My Profile", 0, 0);
        add("&View/&Play Game", 0, 0);
        add("&View/&View Profiles", 0, 0);
        
        add("&Settings/&Game Settings", 0, 0);
        add("&Settings/&Account Settings", 0, 0);
        
        add("&Help/&About", 0, 0, 0);
        add("&Help/&Found bug?", 0, 0, 0);
    };
    
    StatusBar::StatusBar(int x, int y) : Fl_Group(x, y, 0, 0)
    {
        this->size(this->parent()->w() - 20, 100);
        box(FL_UP_BOX);
        
        btn_logout = new Fl_Button(20, this->y() + 10,
            100, 25, "Logout");
        
        statusText = new Fl_Box(FL_BORDER_BOX, 250, this->y() + 10,
            25, 25, "User ");
        statusText->color(FL_RED);
        statusText->align(FL_ALIGN_LEFT);
        
        connectionStatusText = new Fl_Box(FL_BORDER_BOX, 250, this->y() + 50,
            25, 25, "Server ");
        connectionStatusText->color(FL_READ);
        connectionStatusText->align(FL_ALIGN_LEFT);

        end();
    }

}
}