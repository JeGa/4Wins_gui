#include "GraphicalUIGame.h"
#include <string>

namespace view { namespace gui
{

    GraphicalUIGame::GraphicalUIGame() : Fl_Double_Window(800, 600, "Game")
    {
        p1Out = new Fl_Multiline_Output(10, 10, 150, 100);
        p2Out = new Fl_Multiline_Output(p1Out->x() + p1Out->w() + 20, 10, 150, 100);
        statusOut = new Fl_Multiline_Output(p2Out->x() + p2Out->w() + 20, 10,
            150, 100);
        
        field = new GraphicalUIField(10, p1Out->y() + p1Out->h() + 20);
        field->callback(scb_field_clicked, this);
    }

    GraphicalUIGame::~GraphicalUIGame()
    {
    }

    void GraphicalUIGame::displayGame(std::shared_ptr<data::IGame> game)
    {
        // TODO: ??? nullptr
        if (!game)
            return;
            
        this->game = game;
            
        setInfoOutput();
        field->displayGame(game);
        
        int width = statusOut->x() + statusOut->w() + 10;
        if (width < field->w())
            width = field->w();
        size(width + 20, field->y() + field->h() + 10);
    }
    
    void GraphicalUIGame::setInfoOutput()
    {
        std::string turn = "On Turn: " + game->onTurn()->getName();
        statusOut->value(turn.c_str());
        
        p1Out->value(game->getPlayer1()->toString().c_str());
            
        p2Out->value(game->getPlayer2()->toString().c_str());
    }
    
    void GraphicalUIGame::setWinnerOutput(data::IPlayer *winner)
    {
        statusOut->value(("Winner is: " + winner->getName()).c_str());
    }
    
    void GraphicalUIGame::scb_field_clicked(Fl_Widget *w, void *p)
    {
        (static_cast<GraphicalUIGame *>(p))->cb_field_clicked();
    }

    void GraphicalUIGame::cb_field_clicked()
    {
        // Field is clicked
        this->do_callback();
    }

}
}