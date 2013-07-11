#include "GraphicalUI.h"

namespace view
{
    
    GraphicalUI::GraphicalUI()
    {
        manager = factory.getGameManagerLocal(factory.getGameController());
        //window.callback(scb_window, this);
        // window.addCallbacks(this);
    }

    GraphicalUI::~GraphicalUI()
    {
        delete manager;
    }
    
    void GraphicalUI::startLocalGame()
    {
        
    }
    
    void GraphicalUI::run()
    {
        window.show();
        while(Fl::wait());
    }
    
   /* void GraphicalUI::scb_window(Fl_Widget *w, void *p)
    {
        ((GraphicalUI *) p)->cb_window(w);
    }
    
    void GraphicalUI::cb_window(Fl_Widget *w)
    {
        int a;
    }*/

}