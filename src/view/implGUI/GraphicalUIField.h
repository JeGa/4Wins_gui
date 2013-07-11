#ifndef GRAPHICALUIFIELD_H
#define GRAPHICALUIFIELD_H

#include <Fl/Fl_Widget.H> // Base class: Fl_Widget
#include "IField.h"

namespace view { namespace gui
{

    class GraphicalUIField : public Fl_Widget
    {
    private:
        static const int sizeX = 40;
        static const int sizeY = 40;
    public:
        GraphicalUIField();
        virtual ~GraphicalUIField();
        
        void drawField(data::IField *field);
        virtual void draw() override;
    };

}
}

#endif // GRAPHICALUIFIELD_H
