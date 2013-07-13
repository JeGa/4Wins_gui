#include "GraphicalGUIPlayGame.h"

namespace view { namespace gui
{

    GraphicalGUIPlayGame::GraphicalGUIPlayGame() :
        Fl_Group(10, 10, 10, 10)
    {
        this->resize(this->parent()->x(), this->parent()->y() + 20,
            this->parent()->w(), this->parent()->h() - 40);
            
        this->label("My Profile");
        
        end();
    }

    GraphicalGUIPlayGame::~GraphicalGUIPlayGame()
    {
    }

}
}

