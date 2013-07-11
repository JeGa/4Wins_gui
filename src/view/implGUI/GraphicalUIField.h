/*
* Needs the GameManager to draw the field.
*/

#ifndef GRAPHICALUIFIELD_H
#define GRAPHICALUIFIELD_H

#include <Fl/Fl_Widget.H> // Base class: Fl_Widget
#include "IField.h"
#include "IGameManager.h"

namespace view { namespace gui
{
    
    struct CellDrawing;

    class GraphicalUIField : public Fl_Widget
    {
    private:
        controller::IGameManager *manager = nullptr;
        CellDrawing *clickedCell;
        
    public:
        static const int sizeX = 40;
        static const int sizeY = 40;
        
        GraphicalUIField(int x, int y);
        virtual ~GraphicalUIField();
        
        void setGameManager(controller::IGameManager *manager);
        void displayGame();
        bool cellIsClicked(int x, int y);
        CellDrawing *getClickedCell();
        
        virtual void draw() override;
        virtual int handle(int event) override;
    };
    
    // Used for easier drawing and click recognition.
    typedef struct CellDrawing
    {
        int x = 0;
        int xNr = 0;
        int y = 0;
        int yNr = 0;
        int w = GraphicalUIField::sizeX;
        int h = GraphicalUIField::sizeY;
        
        CellDrawing(int xCell, int yCell) : x(xCell), y(yCell) {};
        
        bool isClicked(int x, int y)
        {
            if (x >= this->x && x <= this->x + w)
                if (y >= this->y && y <= this->y + h)
                    return true;
            return false;
        }
    } CellDrawing;

}
}

#endif // GRAPHICALUIFIELD_H