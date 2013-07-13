#ifndef GRAPHICALGUIPLAYGAME_H
#define GRAPHICALGUIPLAYGAME_H

#include "GraphicalUIField.h"
#include <Fl/fl_button.h>
#include <Fl/Fl_Group.h> // Base class: Fl_Group

namespace view { namespace gui
{

    class GraphicalGUIPlayGame : public Fl_Group
    {
    private:
        Fl_Button *play;
    public:
        GraphicalGUIPlayGame();
        virtual ~GraphicalGUIPlayGame();

    };

}
}

#endif // GRAPHICALGUIPLAYGAME_H
