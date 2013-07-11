#ifndef GRAPHICALUITAB_H
#define GRAPHICALUITAB_H

#include <Fl/Fl_Tabs.h>

namespace view { namespace gui
{

    class GraphicalUITab : public Fl_Tabs
    {
    public:
        GraphicalUITab(int x, int y, int w, int h);
        virtual ~GraphicalUITab();

    };

}
}

#endif // GRAPHICALUITAB_H
