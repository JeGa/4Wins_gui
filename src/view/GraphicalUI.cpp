#include "GraphicalUI.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>

namespace view
{

    using namespace controller;
    using namespace data;

    // Callback functions
    /*static void scb_window(Fl_Widget *w, void *data)
    {

    }

    static void scb_menubar(Fl_Widget *w, void *data)
    {
        ((GraphicalUI *) data)->cb_menubar(w);
    }

    static void scb_btn_localGame(Fl_Widget *w, void *data)
    {
        //(Fl_Button *) w)->
    }

    void GraphicalUI::cb_menubar(Fl_Widget *w)
    {
        hide();
    }*/

    GraphicalUI::GraphicalUI()
        : Fl_Window(300, 300, "Tests"), gc(factory.getGameController())
    {
        //callback(scb_window);

        menubar = new Fl_Menu_Bar(0, 0, 400, 25);
        menubar->add("&File/&Open", 0, 0, 0, FL_MENU_DIVIDER);
        //menubar->add("&File/&Quit", 0, scb_menubar, (void *)this);
        menubar->add("&Settings/&Test", 0, 0);
        menubar->add("&Whatever/&Test", 0, 0);

        /*wizard = new Fl_Wizard(20, 40, 200, 200, "wiz");

        btn_localGame = new Fl_Button(50, 100, 50, 50, "local");
        btn_localGame->callback(scb_btn_localGame);*/
    }

    GraphicalUI::~GraphicalUI()
    {
        /*delete menubar;
        delete btn_localGame;*/
    }

    void GraphicalUI::startLocalGame()
    {

    }

    void GraphicalUI::start()
    {
        end();
        show();
        Fl::run();
    }

/*
    void GraphicalUI::drawField()
    {
        IField *field = gc->getGame()->
        int w = gc->getGame()
    }

    void GraphicalUI::startInitWindow()
    {
        Fl_Window init = new Fl_Window(300, 300, "Initial settings");
    }
*/

}
