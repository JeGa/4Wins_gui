#ifndef GRAPHICALUISERVER_H
#define GRAPHICALUISERVER_H

#include <Fl/fl_window.h>
#include <Fl/fl_table.h>
#include <Fl/fl_button.h>
#include <Fl/fl_box.h>
#include <Fl/fl_input.h>
#include <Fl/fl_tabs.h>
#include "GraphicalUITable.h"
#include <memory>
#include "IGameManagerServer.h"
#include "GameFactory.h"

namespace view { namespace gui
{

    class GraphicalUIServer : public Fl_Window
    {
    private:
        std::unique_ptr<controller::IGameManagerServer> server;
        controller::GameFactory factory;
    
        Fl_Tabs *tabs;
        GraphicalUITable *table;
        GraphicalUITable *tablePlayers;
        GraphicalUITable *tableGames;      
  
        Fl_Button *startServer;
        Fl_Button *stopServer;
        Fl_Button *refresh;
        Fl_Box *serverStatus;
        Fl_Input *port;
        Fl_Input *conCount;
        
        void addColHeaders();
        
        //callbacks
        static void scb_startServer(Fl_Widget *w, void *p);
        static void scb_stopServer(Fl_Widget *w, void *p);
        static void scb_refresh(Fl_Widget *w, void *p);
        
        void cb_startServer();
        void cb_stopServer();
        void cb_refresh();
        
//        boost::thread updaterThreadHandle;
//        void updaterThread();
    public:
        GraphicalUIServer();
        virtual ~GraphicalUIServer();
    };

}
}

#endif // GRAPHICALUISERVER_H
