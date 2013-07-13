#include "GraphicalUIField.h"

#include <Fl/fl_draw.h>
#include <Fl/fl.h>
#include "IGame.h"

namespace view { namespace gui
{

    GraphicalUIField::GraphicalUIField(int x, int y) :
        Fl_Widget(x, y, 10, 10), game(nullptr)
    {
        clickedCell = new CellDrawing(0, 0);
    }

    GraphicalUIField::~GraphicalUIField()
    {
        delete clickedCell;
    }
    
    // Sets the game to display and get inputs for and
    // resizes the widget
    void GraphicalUIField::displayGame(data::IGame *game)
    {
        if (game == nullptr)
            return;
            
        this->game = game;
            
        int width = game->getWidth();
        int height = game->getHeight();
        
        this->size(width * sizeX + 20, height * sizeY + 20);
        this->redraw();
    }
    
    bool GraphicalUIField::cellIsClicked(int xClicked, int yClicked)
    {
        if (game == nullptr)
            return false;
            
        int width = game->getWidth();
        int height = game->getHeight();
            
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                int xCell = 10 + x() + i * sizeX;
                int yCell = 10 + y() + j * sizeY;
                
                CellDrawing cell(xCell, yCell);
                
                // Set the coordinates from bottom left, not from top left
                cell.xNr = i;
                cell.yNr = height - 1 - j;
                
                if (cell.isClicked(xClicked, yClicked)) {
                    *clickedCell = cell;
                    return true;
                }
            }
        }
        return false;
    }
    
    CellDrawing *GraphicalUIField::getClickedCell()
    {
        return clickedCell;
    }
    
    void GraphicalUIField::draw()
    {
        if (game == nullptr)
            return;
            
        int width = game->getWidth();
        int height = game->getHeight();
        
        draw_box(FL_DOWN_BOX, x(), y(),
            width * sizeX + 20, height * sizeY + 20, FL_WHITE);
            
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                data::IPlayer *p = game->getCellStatus(i, j);
                
                int xCell = 10 + x() + i * sizeX;
                int yCell = 10 + y() + j * sizeY;
                
                CellDrawing cell(xCell, yCell);
                
                if (game->getPlayer1() == p) {
                   draw_box(FL_DOWN_BOX, cell.x, cell.y, cell.w, cell.h, FL_BLACK);
                } else if (game->getPlayer2() == p) {
                    draw_box(FL_DOWN_BOX, cell.x, cell.y, cell.w, cell.h, FL_BLUE);
                } else {
                    draw_box(FL_DOWN_BOX, cell.x, cell.y, cell.w, cell.h, FL_GRAY);
                }
            }
        }
    }
    
    int GraphicalUIField::handle(int event)
    {
        if (event == FL_PUSH) {
            if (Fl::event_button() == FL_LEFT_MOUSE) {
                if (cellIsClicked(Fl::event_x(), Fl::event_y()))
                    this->do_callback();
            }
        }
        return 0;
    }

}
}

