#include <string>
#include <iostream>
#include "IUserInterface.h"
#include "TextUI.h"
#include "GraphicalUI.h"

using namespace std;
using namespace controller;
using namespace data;

void print_help();
void loop(view::IUserInterface *ui);

enum class GameMode {GUI, TUI, NOT_SELECTED};

int main(int argc, char **argv)
{
    // 0 = gui, 1 = tui (, 2 = both -> not implmented - Observer pattern)
    GameMode status = GameMode::GUI;
    view::IUserInterface *ui = nullptr;

    // Parse command line args
    if (argc > 1) {
        // Copy only first string so its easier
        string str(argv[1]);
        
        if (!str.compare("-h"))
            print_help();
        else if (!str.compare("-gui"))
            status = GameMode::GUI;
        else if (!str.compare("-tui"))
            status = GameMode::TUI;
        else
            print_help();
    }

    if (status == GameMode::TUI) {
        ui = new view::TextUI();
    } else if (status == GameMode::GUI)
        ui = new view::GraphicalUI;

    if (ui) {
        loop(ui);
        delete ui;
    }

    return EXIT_SUCCESS;
}

void loop(view::IUserInterface *ui)
{
    ui->run();
}

void print_help()
{
    cout << "#### 4Wins_basic ####" << endl << endl;
    cout << "Command line options:" << endl;
    cout << "-h\t\t\t" << "Print help (this)" << endl;
    cout << "-gui\t\t\t" << "Start gui mode" << endl;
    cout << "-tui\t\t\t" << "Start tui mode" << endl;
    /*cout << "-log\t\t\ŧ" << "Start logging mode (tui to file + gui)" << endl;
    cout << "-guitui\t\t\t" << "Start gui and tui mode" << endl;*/ // Not impl.
    cout << "No parameter: Gui mode" << endl;
}