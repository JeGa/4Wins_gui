#include "GraphicalUITab.h"

namespace view { namespace gui
{

    GraphicalUITab::GraphicalUITab(int x, int y, int w, int h) :
        Fl_Tabs(x, y, w, h)
    {
        playGame = new GraphicalGUIPlayGame();
        this->add(playGame);
        
        myProfile = new GraphicalGUIMyProfile();
        this->add(myProfile);
        
        viewProfiles = new GraphicalGUIViewProfiles();
        this->add(viewProfiles);
        
        hide();
        end();
    }

    GraphicalUITab::~GraphicalUITab()
    {
    }

}
}

