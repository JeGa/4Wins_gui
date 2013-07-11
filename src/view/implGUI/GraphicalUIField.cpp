#include "GraphicalUIField.h"

#include <Fl/fl_draw.h>

namespace view { namespace gui
{

    GraphicalUIField::GraphicalUIField() :
        Fl_Widget(10, 10, 100, 100)
    {
    }

    GraphicalUIField::~GraphicalUIField()
    {
    }
    
    void GraphicalUIField::drawField(data::IField *field)
    {
        for (int i = 0; i < field->getWidth(); ++i) {
            for (int j = 0; j < field->getHeight(); ++j) {
                fl_draw_box(FL_DOWN_BOX, i * sizeX, j * sizeY,
                    40, 40, FL_BLUE);
            }
        }
        
        fl_draw_box(FL_ROUNDED_BOX, x() + 10, y() + 10,
            w() - 20, h() - 20, FL_GREEN);

    }
    
    void GraphicalUIField::draw()
    {
        
    }

}
}

