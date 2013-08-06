#ifndef GRAPHICALUIVIEWPROFILES_H
#define GRAPHICALUIVIEWPROFILES_H

#include <Fl/Fl_Group.h> // Base class: Fl_Group
#include "GraphicalUITable.h"
#include <Fl/fl_button.h>

namespace view {class GraphicalUI;}

namespace view { namespace gui
{

    class GraphicalUIViewProfiles : public Fl_Group
    {
    private:
        GraphicalUITable *table;
        Fl_Button *btn_viewProfiles;
        
    public:
        GraphicalUIViewProfiles();
        virtual ~GraphicalUIViewProfiles();

        friend class view::GraphicalUI;
    };

}
}

#endif // GRAPHICALUIVIEWPROFILES_H
