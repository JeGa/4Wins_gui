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
#include <Fl/fl_Secret_Input.h>
#include <Fl/Fl_Help_View.h>
#include <Fl/Fl_Value_Slider.h>
#include "GraphicalUI.h"
#include "GraphicalUITab.h"

namespace view {class GraphicalUI;}

namespace view { namespace gui
{
    
    class Menu;
    class MenuBar;
    class StatusBar;

    class GraphicalUIWindow : public Fl_Window
    {
    private:
        Menu *menu;
        MenuBar *menubar;
        StatusBar *status;
        GraphicalUITab *tabs;
        Fl_Help_View *html;

    public:
        GraphicalUIWindow();
        virtual ~GraphicalUIWindow();
        
        friend class view::GraphicalUI;
    };
    
    // Small GUI classes for better separation
    
    // ===============================================================
    
    class Menu : public Fl_Group
    {
        private:
            Fl_Button *btn_localGame;
            Fl_Input *p1Name;
            Fl_Input *p2Name;

            Fl_Button *btn_loginGame;
            Fl_Input *loginName;
            Fl_Secret_Input *loginPassword;
            
            Fl_Button *btn_register;
            Fl_Input *registerName;
            Fl_Secret_Input *registerPassword;
            
            Fl_Value_Slider *hor;
            Fl_Value_Slider *vert;
            
        public:
            Menu(int x, int y);
            virtual ~Menu() {};
        
        friend class view::GraphicalUI;
    };
    
    // ===============================================================
    
    class MenuBar : public Fl_Menu_Bar
    {
        private:
        
        public:
            MenuBar(int w, int h);
            virtual ~MenuBar() {};
        
        friend class view::GraphicalUI;
    };
    
    // ===============================================================

    class StatusBar : public Fl_Group
    {
        private:
            Fl_Button *btn_logout;
            
            Fl_Box *statusText;
            Fl_Image *statusImage;
            
            Fl_Box *connectionStatusText;
            Fl_Image *connectionStatusImage;
        public:
            StatusBar(int x, int y);
            virtual ~StatusBar() {};
        
        friend class view::GraphicalUI;
    };

}
}

#endif // GRAPHICALUIWINDOW_H
