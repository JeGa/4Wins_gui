#include "TCPMessageUser.h"

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <cstdlib>

namespace controller
{

    bool TCPMessageUser::parseQueryUserData()
    {
        std::vector<std::string> tokens;
        split(getQueryUserData(), ' ', tokens);

        if (tokens.size() != 4)
            return false;

        if (tokens[0].length() != 2)
            return false;

        tokens[0].erase(1);
        QUERY_MSG_TYPE_USER tmpType = stringToQueryMsgType(tokens[0]);

        if (tmpType == QUERY_MSG_TYPE_USER::NOT_SET)
            return false;

        std::string userKey =  tokens[1];
        std::string userName = tokens[2];
        std::string userPw = tokens[3];

        queryUser = factory.getPlayer(userName, userPw);
        queryType = tmpType;

        return true;
    }

    bool TCPMessageUser::parseAckUserData()
    {
        // Can be empty, if frameData is from a query.
        if (getAckUserData() == "")
            return true;

        std::vector<std::string> tokens;
        split(getAckUserData(), ':', tokens);

        if (tokens.size() != 2)
            return false;

        if (tokens[0].length() != 1)
            return false;

        ACK_MSG_TYPE_USER tmpType = stringToAckMsgType(tokens[0]);
        tokens.erase(tokens.begin());

        if (tmpType == ACK_MSG_TYPE_USER::NOT_SET)
            return false;

        ackType = tmpType;
        queryType = ackToQueryMsgType(ackType);

        boost::algorithm::trim(tokens[0]);

        if (ackType == ACK_MSG_TYPE_USER::GET_PLAYERS_ACK) {
            ackStatus = parsePlayersData(tokens[0]);
        } else {
            if (tokens[0] == "SUCCESS")
                ackStatus = true;
            else if (tokens[0] == "FAILURE")
                ackStatus = false;
        }

        return ackStatus;
    }

    bool TCPMessageUser::parsePlayersData(std::string& playersList)
    {
        players.clear();

        std::vector<std::string> tokens;
        split(playersList, '#', tokens);

        std::cout << "Size of vector: " << tokens.size() << std::endl;

        for (auto& i : tokens) {
            std::vector<std::string> tmp;
            split(i, ' ', tmp);

            if (tmp.size() != 7)
                return false;

            int key = stringToInt(tmp[0]);
            std::string name = tmp[1];
            int wins = stringToInt(tmp[2]);
            int looses = stringToInt(tmp[3]);
            int played = stringToInt(tmp[4]);
            int ratio = stringToDouble(tmp[5]);

            bool loggedin;
            try {
                loggedin = boost::lexical_cast<bool>(tmp[6]);
            } catch (std::exception& e) {
                std::cerr << "Error casting string " << tmp[6] << " to bool: " << e.what() << std::endl;
            }

            std::shared_ptr<data::IPlayer> p(factory.getPlayer(name, ""));
            p->setAllData(key, wins, looses, played, ratio, loggedin);
            players[p->getKey()] = p;
        }
        return true;
    }

    /*
     * All the conversion stuff.
     */

    std::string TCPMessageUser::intToString(int v)
    {
        std::string str;
        try {
            str = boost::lexical_cast<std::string>(v);
        } catch (std::exception& e) {
            std::cerr << "Error casting int " << v << " to string: " << e.what() << std::endl;
            return "";
        }
        return str;
    }

    std::string TCPMessageUser::doubleToString(double v)
    {
        std::string str;
        try {
            str = boost::lexical_cast<std::string>(v);
        } catch (std::exception& e) {
            std::cerr << "Error casting double " << v << " to string: " << e.what() << std::endl;
            return "";
        }
        return str;
    }

    int TCPMessageUser::stringToInt(std::string v)
    {
        int integer;
        try {
            integer = boost::lexical_cast<int>(v);
        } catch (std::exception& e) {
            std::cerr << "Error casting string " << v << " to int: " << e.what() << std::endl;
            return -1;
        }
        return integer;
    }

    double TCPMessageUser::stringToDouble(std::string v)
    {
        double dbl;
        try {
            dbl = boost::lexical_cast<double>(v);
        } catch (std::exception& e) {
            std::cerr << "Error casting string " << v << " to double: " << e.what() << std::endl;
            return -1.0;
        }
        return dbl;
    }

    std::string TCPMessageUser::playerToMessageString(data::IPlayer& p)
    {
        std::string tmp;

        std::string tmpKey =  boost::lexical_cast<std::string>(p.getKey());
        std::string tmpName = p.getName();
        std::string tmpPw = p.getPassword();

        tmp = tmpKey + " " + tmpName + " " + tmpPw;

        return tmp;
    }

    std::string TCPMessageUser::queryMsgTypeUserToString(QUERY_MSG_TYPE_USER type)
    {
        std::string str;
        try {
            int typeInt = static_cast<int>(type);
            str = boost::lexical_cast<std::string>(typeInt);
        } catch (std::exception& e) {
            std::cerr << "queryMsgTypeUserToString: " << e.what() << std::endl;
            return "";
        }
        return str;
    }

    std::string TCPMessageUser::ackMsgTypeUserToString(ACK_MSG_TYPE_USER type)
    {
        std::string str;
        try {
            int typeInt = static_cast<int>(type);
            str = boost::lexical_cast<std::string>(typeInt);
        } catch (std::exception& e) {
            std::cerr << "ackMsgTypeUserToString: " << e.what() << std::endl;
            return "";
        }
        return str;
    }

    QUERY_MSG_TYPE_USER TCPMessageUser::stringToQueryMsgType(std::string type)
    {
        QUERY_MSG_TYPE_USER tmpType;
        try {
            int typeInt = boost::lexical_cast<int>(type);
            tmpType = static_cast<QUERY_MSG_TYPE_USER>(typeInt);
        } catch (std::exception& e) {
            std::cerr << "stringToQueryMsgType: " << e.what() << std::endl;
            return QUERY_MSG_TYPE_USER::NOT_SET;
        }
        return tmpType;
    }

    ACK_MSG_TYPE_USER TCPMessageUser::stringToAckMsgType(std::string type)
    {
        ACK_MSG_TYPE_USER tmpType;
        try {
            int typeInt = boost::lexical_cast<int>(type);
            tmpType = static_cast<ACK_MSG_TYPE_USER>(typeInt);
        } catch (std::exception& e) {
            std::cerr << "stringToAckMsgType: " << e.what() << std::endl;
            return ACK_MSG_TYPE_USER::NOT_SET;
        }
        return tmpType;
    }

    ACK_MSG_TYPE_USER TCPMessageUser::queryToAckMsgType(QUERY_MSG_TYPE_USER type)
    {
        return static_cast<ACK_MSG_TYPE_USER>(type);
    }

    QUERY_MSG_TYPE_USER TCPMessageUser::ackToQueryMsgType(ACK_MSG_TYPE_USER type)
    {
        return static_cast<QUERY_MSG_TYPE_USER>(type);
    }

    std::vector<std::string>& TCPMessageUser::split(
        const std::string& s,
        char delim,
        std::vector<std::string>& elems)
    {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    // ===============================================================

    bool TCPMessageUser::createQueryMessage(
        QUERY_MSG_TYPE_USER type,
        std::shared_ptr<data::IPlayer> p)
    {
        if (type == QUERY_MSG_TYPE_USER::NOT_SET)
            return false;

        std::string tmpQueryData = queryMsgTypeUserToString(type)
                                   + ": " + playerToMessageString(*p);

        queryType = type;
        queryUser = p;
        return TCPMessage::createQueryMessage(tmpQueryData);
    }

    bool TCPMessageUser::createMessage(std::string frameData)
    {
        if (!TCPMessage::createMessage(frameData))
            return false;

        if (!parseQueryUserData())
            return false;

        if (!parseAckUserData())
            return false;

        return true;
    }

    bool TCPMessageUser::setAckMessage(bool status)
    {
        if (queryType == QUERY_MSG_TYPE_USER::NOT_SET ||
                queryType == QUERY_MSG_TYPE_USER::GET_PLAYERS_QUERY)
            return false;

        ackType = queryToAckMsgType(queryType);
        std::string tmp = ackMsgTypeUserToString(ackType);

        if (status)
            tmp += ": SUCCESS";
        else
            tmp += ": FAILURE";

        return TCPMessage::setAckMessage(tmp);
    }

    bool TCPMessageUser::setAckMessage(
        std::map<int, std::shared_ptr<data::IPlayer>>& players)
    {
        if (queryType != QUERY_MSG_TYPE_USER::GET_PLAYERS_QUERY)
            return false;

        ackType = queryToAckMsgType(queryType);
        std::string tmp = ackMsgTypeUserToString(ackType);
        tmp += ":";

        for (auto& i : players) {
            tmp += intToString(i.second->getKey());
            tmp += " " + i.second->getName();
            tmp += " " + intToString(i.second->getWins());
            tmp += " " + intToString(i.second->getLooses());
            tmp += " " + intToString(i.second->getPlayedGames());
            tmp += " " + doubleToString(1.0);//i.second->getWinRatio()); // TODO
            tmp += " " + intToString(i.second->isLoggedIn());
            tmp += "#";
        }

        return TCPMessage::setAckMessage(tmp);
    }

    void TCPMessageUser::reset()
    {
        queryUser.reset();
        players.clear();
        TCPMessage::reset();
    }

    QUERY_MSG_TYPE_USER TCPMessageUser::getQueryType()
    {
        return queryType;
    }

    bool TCPMessageUser::getAckStatus()
    {
        return ackStatus;
    }

    std::shared_ptr<data::IPlayer> TCPMessageUser::getUser()
    {
        return queryUser;
    }

    std::map<int, std::shared_ptr<data::IPlayer>> TCPMessageUser::getPlayers()
    {
        return players;
    }

}
