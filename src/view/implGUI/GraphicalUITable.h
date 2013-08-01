/*
* Based on the FLTK example "table-simple.cxx".
*/

#ifndef GRAPHICALUITABLE_H
#define GRAPHICALUITABLE_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>
#include <vector>
#include <string>

namespace view { namespace gui
{

    class GraphicalUITable : public Fl_Table
    {
    private:
        // The rows
        std::vector<std::vector<std::string>> data;
  
        int rowsNr = 0;
        int colsNr = 0;
        std::vector<std::string> colHeader;
    
        void DrawHeader(const char *s, int X, int Y, int W, int H);
        void DrawData(const char *s, int X, int Y, int W, int H);
        void draw_cell(TableContext context, int ROW=0, int COL=0,
                       int X=0, int Y=0, int W=0, int H=0);
    public:
        GraphicalUITable(int X, int Y, int W, int H, const char *L=0);
        void addColHeader(std::string c);
        void addRow(std::vector<std::string> r);
        void clearRows();
    };

}
}

#endif
