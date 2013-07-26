#ifndef GRAPHICALUITAB_H
#define GRAPHICALUITAB_H

#include "GraphicalUIPlayGame.h"
#include "GraphicalUIMyProfile.h"
#include "GraphicalUIViewProfiles.h"
#include <Fl/Fl_Tabs.h>

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

    };

}
}

#endif // GRAPHICALUITAB_H
