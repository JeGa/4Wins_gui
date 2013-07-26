#include "GraphicalUITab.h"

namespace view { namespace gui
{

    GraphicalUITab::GraphicalUITab(int x, int y, int w, int h) :
        Fl_Tabs(x, y, w, h)
    {
        playGame = new GraphicalUIPlayGame();
        this->add(playGame);
        
        myProfile = new GraphicalUIMyProfile();
        this->add(myProfile);
        
        viewProfiles = new GraphicalUIViewProfiles();
        this->add(viewProfiles);
        
        hide();
        end();
    }

    GraphicalUITab::~GraphicalUITab()
    {
    }

}
}

