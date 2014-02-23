#include "GraphicalUIServer.h"

#include <Fl/fl.h>
#include <boost/lexical_cast.hpp>

namespace view { namespace gui
{

    GraphicalUIServer::GraphicalUIServer()
        : Fl_Window(700, 500, "4Wins Server")/*,
        server(factory.getGameManagerServer(factory.getGameController()))*/
    {
        startServer = new Fl_Button(20, 10,
            100, 25, "Start Server");
            
        stopServer = new Fl_Button(20, 40,
            100, 25, "Stop Server");
            
        refresh = new Fl_Button(400, 10,
            100, 25, "Refresh");
            
        conCount = new Fl_Input(220, 10, 100, 25, "Connections");
        
        serverStatus = new Fl_Box(FL_BORDER_BOX, 400, this->y() + 40,
            25, 25, "");
        serverStatus->color(FL_RED);
        serverStatus->align(FL_ALIGN_LEFT);
            
        port = new Fl_Input(220, 40, 100, 25);
        port->label("Server port ");
        
        // Tab group
        
        tabs = new Fl_Tabs(20, 100, 660, 380);
        
        table = new GraphicalUITable(tabs->x(), tabs->y() + 20, tabs->w(),
            tabs->h() - 20, "Connections");
        tabs->add(table);
        
        tablePlayers = new GraphicalUITable(tabs->x(), tabs->y() + 20, tabs->w(),
            tabs->h() - 20, "Players");
        tabs->add(tablePlayers);
        
        tableGames = new GraphicalUITable(tabs->x(), tabs->y() + 20, tabs->w(),
            tabs->h() - 20, "Games");
        tabs->add(tableGames);
        
        addColHeaders();
        
        tabs->end();
        
        // Add callbacks
        startServer->callback(scb_startServer, this);
        stopServer->callback(scb_stopServer, this);
        refresh->callback(scb_refresh, this);
        
        this->end();
        
        Fl::add_timeout(0.5, s_updateHandler, this);
    }

    GraphicalUIServer::~GraphicalUIServer()
    {
        //server->stop();
    }
    
    void GraphicalUIServer::addColHeaders()
    {
        table->clearRows();
        tablePlayers->clearRows();
        tableGames->clearRows();
        
        table->addColHeader("Address");
        table->addColHeader("Port");
        table->addColHeader("Logged-in");
        
        tablePlayers->addColHeader("Key");
        tablePlayers->addColHeader("Name");
        tablePlayers->addColHeader("Wins");
        tablePlayers->addColHeader("Looses");
        tablePlayers->addColHeader("Played Games");
        tablePlayers->addColHeader("Win Ratio");
        tablePlayers->addColHeader("Logged In");
        
        tableGames->addColHeader("Key");
        tableGames->addColHeader("Player1");
        tableGames->addColHeader("Player2");
        tableGames->addColHeader("Is Running");
        tableGames->addColHeader("Winner");
    }
    
    void GraphicalUIServer::scb_startServer(Fl_Widget *w, void *p)
    {
        (static_cast<GraphicalUIServer*>(p))->cb_startServer();
    }
    
    void GraphicalUIServer::scb_stopServer(Fl_Widget *w, void *p)
    {
        (static_cast<GraphicalUIServer*>(p))->cb_stopServer();
    }
        
    void GraphicalUIServer::cb_startServer()
    {
        //server->start();
        
        serverStatus->color(FL_GREEN);
        serverStatus->redraw();
    }
    
    void GraphicalUIServer::cb_stopServer()
    {
        //server->stop();
        
        serverStatus->color(FL_RED);
        serverStatus->redraw();
    }
    
    void GraphicalUIServer::scb_refresh(Fl_Widget *w, void *p)
    {
        (static_cast<GraphicalUIServer*>(p))->cb_refresh();
    }
    
    void GraphicalUIServer::cb_refresh()
    {
        addColHeaders();
        
        /*std::vector<std::unique_ptr<controller::TCPConnection>>& cons =
            server->getConnections();
        
        int s = cons.size();
        std::string tmp = boost::lexical_cast<std::string>(s);
        conCount->value(tmp.c_str());
       
        for (std::unique_ptr<controller::TCPConnection>& i : cons) {
            std::vector<std::string> row;
            
            std::string t2 = i->getRemoteAddress();
            
            row.push_back(i->getRemoteAddress());
            row.push_back(boost::lexical_cast<std::string>(i->getRemotePort()));
            row.push_back("No");
            
            table->addRow(row);
        }
        
        std::map<int, data::IPlayer *> players = server->getPlayers();
        
        for (auto &i : players) {
            std::vector<std::string> row;
            
            row.push_back(boost::lexical_cast<std::string>(i.second->getKey()));
            row.push_back(i.second->getName());
            row.push_back(boost::lexical_cast<std::string>(i.second->getWins()));
            row.push_back(boost::lexical_cast<std::string>(i.second->getLooses()));
            row.push_back(boost::lexical_cast<std::string>(i.second->getPlayedGames()));
            row.push_back(boost::lexical_cast<std::string>(i.second->getWinRatio()));
            row.push_back(boost::lexical_cast<std::string>(i.second->isLoggedIn()));
            
            tablePlayers->addRow(row);
        }*/
        
        table->redraw();
        tablePlayers->redraw();
        tableGames->redraw();
    }
    
    void GraphicalUIServer::s_updateHandler(void *p)
    {
        (static_cast<GraphicalUIServer*>(p))->updateHandler();
    }
    
    void GraphicalUIServer::updateHandler()
    {
        cb_refresh();
        Fl::repeat_timeout(0.5, s_updateHandler, this);
    }
    
}
}