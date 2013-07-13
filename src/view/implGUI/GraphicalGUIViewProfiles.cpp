#include "GraphicalGUIViewProfiles.h"

namespace view { namespace gui
{

    GraphicalGUIViewProfiles::GraphicalGUIViewProfiles() :
        Fl_Group(10, 10, 10, 10)
    {
        this->resize(this->parent()->x(), this->parent()->y() + 20,
            this->parent()->w(), this->parent()->h() - 40);
            
        this->label("View Profiles");
        
        end();
    }

    GraphicalGUIViewProfiles::~GraphicalGUIViewProfiles()
    {
    }

}
}

