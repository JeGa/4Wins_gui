#include "TextUI.h"

#include "GameFactory.h"
#include "IGame.h"
#include "GameControllerStrategy.h"
#include <string>
#include <iostream>

namespace view
{

    using namespace controller;
    using namespace data;
    using namespace std;

    TextUI::TextUI() : gc(factory.getGameController())
    {
        cout << "####################################" << endl;
        cout << "#### 4Wins: Text User Interface ####" << endl;
        cout << "####################################" << endl;
    }

    TextUI::~TextUI()
    {
        if (gc->isRunning())
            delete game;

        delete gc;

        delete p1;
        delete p2;
    }

    void TextUI::menu()
    {
        int choose;
        cout << "---- 4Wins Menu ----" << endl;
        cout << "1) Local 2 player game" << endl;
        cout << "2) Network game" << endl << endl;

        cin >> choose;
        if (choose == 1)
            startLocalGame();
        else if (choose == 2)
            throw "Not implemented";
    }

    void TextUI::startLocalGame()
    {
        string p1_name, p2_name;
        int w, h;

        cout << endl << "#### Local 2 player game ####" << endl;
        cout << "Set up:" << endl;

        cout << "Width and height: ";
        cin >> w;
        cin >> h;
        cout << "Player1 name: ";
        cin >> p1_name;
        cout << "Player2 name: ";
        cin >> p2_name;

        p1 = factory.getPlayer(p1_name, "local");
        p2 = factory.getPlayer(p2_name, "local");

        game = factory.getGame(w, h, p1, p2, p1);

        gc->playGame(game);
        cout << endl << toString() << endl;
    }

    bool TextUI::setInput(int x, int y)
    {
        if (!gc->isRunning()) {
            throw "First start a game.";
        }

        if (!gc->toggleTurn(x, y))
            cout << "Not valid cell, try again!";

        if (!gc->isRunning()) {
            cout << "#### Game ends ####" << endl;
            cout << "WINNER IS:" << endl;
            cout << gc->getLastWinner()->toString() << endl;
            return false;
        }

        cout << toString();
        return true;
    }

    std::string TextUI::toString()
    {
        return game->toString();
    }

}
