#include "GraphicalUIMyProfile.h"

namespace view { namespace gui
{

    GraphicalUIMyProfile::GraphicalUIMyProfile() :
        Fl_Group(10, 10, 10, 10)
    {
        this->resize(this->parent()->x(), this->parent()->y() + 20,
            this->parent()->w(), this->parent()->h() - 40);
            
        this->label("Play Game");
        
        end();
    }

    GraphicalUIMyProfile::~GraphicalUIMyProfile()
    {
    }

}
}

