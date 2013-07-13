#ifndef GRAPHICALUIGAME_H
#define GRAPHICALUIGAME_H

#include <Fl/Fl_Double_Window.h> // Base class: Fl_Window
#include "GraphicalUIField.h"
#include <Fl/Fl_Multiline_output.h>

namespace view {class GraphicalUI;}

namespace view { namespace gui
{

    class GraphicalUIGame : public Fl_Double_Window
    {
    private:
        GraphicalUIField *field;
        data::IGame *game; // Active game for this window
        
        Fl_Multiline_Output *p1Out;
        Fl_Multiline_Output *p2Out;
        Fl_Multiline_Output *statusOut;
        
    public:
        GraphicalUIGame();
        virtual ~GraphicalUIGame();
        
        void displayGame(data::IGame *game);
        void setWinnerOutput(data::IPlayer *winner);
        void setInfoOutput();
        
        static void scb_field_clicked(Fl_Widget *w, void *p);
        void cb_field_clicked();

        friend class view::GraphicalUI;
    };

}
}

#endif // GRAPHICALUIGAME_H
