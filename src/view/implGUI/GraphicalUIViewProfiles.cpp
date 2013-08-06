#include "GraphicalUIViewProfiles.h"

namespace view { namespace gui
{

    GraphicalUIViewProfiles::GraphicalUIViewProfiles() :
        Fl_Group(10, 10, 10, 10)
    {
        this->resize(this->parent()->x(), this->parent()->y() + 20,
            this->parent()->w(), this->parent()->h() - 40);
            
        this->label("View Profiles");
        
        table = new GraphicalUITable(x() + 20, y() + 50, w() - 40, h() - 80);
        btn_viewProfiles = new Fl_Button(x() + 20, y() + 20, 100, 20, "Get Data");
        
        end();
    }

    GraphicalUIViewProfiles::~GraphicalUIViewProfiles()
    {
    }

}
}

