#define RELEASE
#ifdef RELEASE

#include <string>
#include <iostream>
#include "TextUI.h"
//#include "GraphicalUI.h"

using namespace std;
using namespace controller;
using namespace data;

void print_help();
void guiLoop();
void tuiLoop();

int main(int argc, char **argv)
{
    // 0 = gui, 1 = tui, 2 = both
    int status = 0;

    // Parse command line args
    if (argc == 1)
        status = 0;
    else {
        // Copy only first string so its easier
        string str(argv[1]);
        if (str.compare("-h") == 0) {
            print_help();
            return 0;
        } else if (str.compare("-gui") == 0)
            status = 0;
        else if (str.compare("-tui") == 0)
            status = 1;
        else {
            print_help();
            return 0;
        }
    }

    //if (status == 0)
        //guiLoop();
    //else if (status == 1)
        tuiLoop();

    return 0;
}

void guiLoop()
{
    //view::GraphicalUI gui;
    //gui.start();
}

void tuiLoop()
{
    view::TextUI tui;
    int x, y;

    tui.menu();
    do {
        cout << "Give x and y coordinates to set cell:" << endl;
        cin >> x;
        cin >> y;

    } while(tui.setInput(x, y));
}

void print_help()
{
    cout << "#### 4Wins_basic ####" << endl << endl;
    cout << "Command line options:" << endl;
    cout << "-h\t\t\t" << "Print help (this)" << endl;
    cout << "-gui\t\t\t" << "Start gui mode" << endl;
    cout << "-tui\t\t\t" << "Start tui mode" << endl;
    /*cout << "-log\t\t\ŧ" << "Start logging mode (tui to file + gui)" << endl;
    cout << "-guitui\t\t\t" << "Start gui and tui mode" << endl;*/
    cout << "No parameter: Gui mode" << endl;
}

#endif
