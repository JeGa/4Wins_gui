#include "GraphicalUITable.h"

namespace view { namespace gui
{

    void GraphicalUITable::DrawHeader(const char* s, int X, int Y, int W, int H)
    {
        fl_push_clip(X,Y,W,H);
        fl_draw_box(FL_THIN_UP_BOX, X,Y,W,H, row_header_color());
        fl_color(FL_BLACK);
        fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
        fl_pop_clip();
    }

    void GraphicalUITable::DrawData(const char* s, int X, int Y, int W, int H)
    {
        fl_push_clip(X,Y,W,H);
        // Draw cell bg
        fl_color(FL_WHITE);
        fl_rectf(X,Y,W,H);
        // Draw cell data
        fl_color(FL_GRAY0);
        fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
        // Draw box border
        fl_color(color());
        fl_rect(X,Y,W,H);
        fl_pop_clip();
    }

    void GraphicalUITable::draw_cell(TableContext context, int ROW, int COL,
                                     int X, int Y, int W, int H)
    {
        static char s[40];
        switch (context) {
            case CONTEXT_STARTPAGE:                   // before page is drawn..
                fl_font(FL_HELVETICA, 16);            // set the font for our drawing operations
                return;
            case CONTEXT_COL_HEADER:                  // Draw column headers
                DrawHeader(colHeader[COL].c_str(), X, Y, W, H);
                return;
            case CONTEXT_ROW_HEADER:                  // Draw row headers
                sprintf(s, "%03d:", ROW);             // "001:", "002:", etc
                DrawHeader(s, X, Y, W, H);
                return;
            case CONTEXT_CELL:                        // Draw data in cells
                DrawData(data[ROW][COL].c_str(), X, Y, W, H);
                return;
            default:
                return;
        }
    }
    
    GraphicalUITable::GraphicalUITable(int X, int Y, int W, int H, const char* L)
        : Fl_Table(X,Y,W,H,L)
    {        
        // Rows
        rows(rowsNr);             // how many rows
        row_header(1);              // enable row headers (along left)
        row_height_all(20);         // default height of rows
        row_resize(0);              // disable row resizing
        // Cols
        cols(colsNr);             // how many columns
        col_header(1);              // enable column headers (along top)
        col_width_all(100);          // default width of columns
        col_resize(1);              // enable column resizing
        end(); // end the Fl_Table group
    }
    
    void GraphicalUITable::addRow(std::vector<std::string> r)
    {
        if (r.size() != colsNr)
            return;
            
        data.push_back(r);
        ++rowsNr;
        rows(rowsNr);
        
        redraw();
    }
    
    void GraphicalUITable::addColHeader(std::string c)
    {
        colHeader.push_back(c);
        ++colsNr;
        cols(colsNr);
        
        redraw();
    }
    
    void GraphicalUITable::clearRows()
    {
        data.clear();
        colsNr = 0;
        rowsNr = 0;
    
        clear();
    }

}
}



