#include "GraphicalUIField.h"

#include <Fl/fl_draw.h>
#include <Fl/fl.h>
#include "IGame.h"

namespace view { namespace gui
{

    GraphicalUIField::GraphicalUIField(int x, int y) :
        Fl_Widget(x, y, 10, 10)
    {
        clickedCell = new CellDrawing(0, 0);
    }

    GraphicalUIField::~GraphicalUIField()
    {
        delete clickedCell;
    }
    
    void GraphicalUIField::setGameManager(controller::IGameManager *manager)
    {
        this->manager = manager;
    }
    
    void GraphicalUIField::displayGame()
    {
        if (this->manager == nullptr ||
            this->manager->getGameController()->getGame() == nullptr)
            return;
        
        // Resize
        data::IGame *game = this->manager->getGame();
            
        int width = game->getWidth();
        int height = game->getHeight();
        
        this->size(width * sizeX + 20, height * sizeY + 20);
        this->redraw();
    }
    
    bool GraphicalUIField::cellIsClicked(int xClicked, int yClicked)
    {
        data::IGame *game = this->manager->getGame();
            
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
        if (this->manager == nullptr ||
            this->manager->getGameController()->getGame() == nullptr)
            return;
        
        data::IGame *game = this->manager->getGame();
            
        int width = game->getWidth();
        int height = game->getHeight();

        //game->getCellStatus();
        
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

