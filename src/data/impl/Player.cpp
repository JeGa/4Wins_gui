#include "Player.h"

#include <string>
#include <sstream>
#include <fstream>

namespace data
{
    const int IPlayer::LOOSE;
    const int IPlayer::WIN;

    Player::Player(std::string name, std::string pw)
        : name(name), password(pw), wins(0), looses(0), playedGames(0), winRatio(0.0)
    {

    }

    Player::~Player()
    {

    }

    std::string Player::getName()
    {
        return name;
    }

    void Player::writeToDisk()
    {
        std::ofstream out((name + ".player").c_str(), std::ios::binary);

        if (!out)
            throw "Could not open output filestream.";

        out << toString();

        out.close(); // Flush buffer
    }

    /*bool Player::verifypassword(std::string pw)
    {

    }*/

    void Player::addGameStatistic(int result)
    {
        if (result == WIN) {
            wins++;
            playedGames++;
        } else if (result == LOOSE) {
            looses++;
            playedGames++;
        } else
            throw "Add game statistics: Wrong argument.";

        winRatio = getWinRatio();
    }

    int Player::getWins()
    {
        return wins;
    }

    int Player::getLooses()
    {
        return looses;
    }

    int Player::getPlayedGames()
    {
        return playedGames;
    }

    double Player::getWinRatio()
    {
        return static_cast<double>(wins)/playedGames;
    }

    std::string Player::toString()
    {
        std::string str;
        std::stringstream sstr;
        str += "Player: " + name + '\n';
        sstr << "Wins: " << wins << '\n' << "Looses: " << looses << '\n';
        sstr << "Ratio: " << winRatio << '\n';
        str += sstr.str();

        return str;
    }

}
