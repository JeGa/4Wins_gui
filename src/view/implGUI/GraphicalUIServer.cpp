#include "GraphicalUIServer.h"

namespace view { namespace gui
{

    GraphicalUIServer::GraphicalUIServer()
        : Fl_Window(200, 200, "4Wins Server")
    {
        
        this->end();
    }

    GraphicalUIServer::~GraphicalUIServer()
    {
    }

}
}