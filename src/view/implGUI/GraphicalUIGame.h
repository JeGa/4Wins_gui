#ifndef GRAPHICALUIGAME_H
#define GRAPHICALUIGAME_H

#include <Fl/Fl_Double_Window.h> // Base class: Fl_Window
#include "GraphicalUIField.h"
#include <Fl/Fl_Multiline_output.h>
#include <memory>

namespace view {class GraphicalUI;}

namespace view { namespace gui
{

    class GraphicalUIGame : public Fl_Double_Window
    {
    private:
        GraphicalUIField *field;
        // Active game for this window
        std::shared_ptr<data::IGame> game;
        
        Fl_Multiline_Output *p1Out;
        Fl_Multiline_Output *p2Out;
        Fl_Multiline_Output *statusOut;
        
    public:
        GraphicalUIGame();
        virtual ~GraphicalUIGame();
        
        void displayGame(std::shared_ptr<data::IGame> game);
        void setWinnerOutput(data::IPlayer *winner); // Ptr is okay
        void setInfoOutput();
        
        static void scb_field_clicked(Fl_Widget *w, void *p);
        void cb_field_clicked();

        friend class view::GraphicalUI;
    };

}
}

#endif // GRAPHICALUIGAME_H
