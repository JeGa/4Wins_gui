#ifndef GRAPHICALUISERVER_H
#define GRAPHICALUISERVER_H

#include <Fl/fl_window.h>

namespace view { namespace gui
{

    class GraphicalUIServer : public Fl_Window
    {
    public:
        GraphicalUIServer();
        virtual ~GraphicalUIServer();

    };

}
}

#endif // GRAPHICALUISERVER_H
