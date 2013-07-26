#ifndef GRAPHICALUIPLAYGAME_H
#define GRAPHICALUIPLAYGAME_H

#include "GraphicalUIField.h"
#include <Fl/fl_button.h>
#include <Fl/Fl_Group.h> // Base class: Fl_Group

namespace view { namespace gui
{

    class GraphicalUIPlayGame : public Fl_Group
    {
    private:
        Fl_Button *play;
    public:
        GraphicalUIPlayGame();
        virtual ~GraphicalUIPlayGame();

    };

}
}

#endif // GRAPHICALUIPLAYGAME_H
