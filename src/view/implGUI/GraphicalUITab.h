#ifndef GRAPHICALUITAB_H
#define GRAPHICALUITAB_H

#include "GraphicalUIPlayGame.h"
#include "GraphicalUIMyProfile.h"
#include "GraphicalUIViewProfiles.h"
#include <Fl/Fl_Tabs.h>

namespace view {class GraphicalUI;}

namespace view { namespace gui
{

    class GraphicalUITab : public Fl_Tabs
    {
    private:
        // Tabs to display
        GraphicalUIPlayGame *playGame;
        GraphicalUIMyProfile *myProfile;
        GraphicalUIViewProfiles *viewProfiles;
        
    public:
        GraphicalUITab(int x, int y, int w, int h);
        virtual ~GraphicalUITab();

        friend class view::GraphicalUI;
    };

}
}

#endif // GRAPHICALUITAB_H
