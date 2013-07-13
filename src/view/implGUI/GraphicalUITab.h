#ifndef GRAPHICALUITAB_H
#define GRAPHICALUITAB_H

#include "GraphicalGUIPlayGame.h"
#include "GraphicalGUIMyProfile.h"
#include "GraphicalGUIViewProfiles.h"
#include <Fl/Fl_Tabs.h>

namespace view { namespace gui
{

    class GraphicalUITab : public Fl_Tabs
    {
    private:
        // Tabs to display
        GraphicalGUIPlayGame *playGame;
        GraphicalGUIMyProfile *myProfile;
        GraphicalGUIViewProfiles *viewProfiles;
        
    public:
        GraphicalUITab(int x, int y, int w, int h);
        virtual ~GraphicalUITab();

    };

}
}

#endif // GRAPHICALUITAB_H
