#include "TCPMessageUser.h"

#include <boost/lexical_cast.hpp>
#include <sstream>
#include <cstdlib>

namespace controller
{

    bool TCPMessageUser::tokenizeUserMessage(
        std::string msg,
        std::vector<std::string>& tokens)
    {
        // Tokenize the string
        std::stringstream sstr(msg);
        while (sstr.good()) {
            std::string tmpStr;
            sstr >> tmpStr;
            tokens.push_back(tmpStr);
        }

        if (tokens.size() < 2)
            return false;

        if (tokens[0].length() != 2)
            return false;

        tokens[0].erase(1);

        return true;
    }

    bool TCPMessageUser::parseQueryUserData()
    {
        std::vector<std::string> tokens;

        if (!tokenizeUserMessage(getQueryUserData(), tokens))
            return false;

        if (tokens.size() != 4)
            return false;

        // Query type
        int tmpTypeInt = boost::lexical_cast<int>(tokens[0]);

        QUERY_MSG_TYPE_USER tmpType;
        try {
            tmpType = static_cast<QUERY_MSG_TYPE_USER>(tmpTypeInt);
        } catch (boost::bad_lexical_cast& e) {
            return false;
        }

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
        std::vector<std::string> tokens;

        if (!tokenizeUserMessage(getAckUserData(), tokens))
            return false;

        if (tokens.size() <= 1)
            return false;

        // Ack type
        int tmpTypeInt = boost::lexical_cast<int>(tokens[0]);

        ACK_MSG_TYPE_USER tmpType;
        try {
            tmpType = static_cast<ACK_MSG_TYPE_USER>(tmpTypeInt);
        } catch (boost::bad_lexical_cast& e) {
            return false;
        }

        if (tmpType == ACK_MSG_TYPE_USER::NOT_SET)
            return false;

        queryType = static_cast<QUERY_MSG_TYPE_USER>(tmpTypeInt);
        ackType = tmpType;

        if (tmpType == ACK_MSG_TYPE_USER::GET_PLAYERS_ACK) {
            parsePlayersData();
            ackStatus = true;

        } else {
            if (tokens[1] == "SUCCESS")
                ackStatus = true;
            else if (tokens[1] == "FAILURE")
                ackStatus = false;
        }

        return true;
    }

    void TCPMessageUser::parsePlayersData()
    {
        players.clear();

        std::stringstream sstr;
        std::string tmp = "";
        std::vector<std::string> tokens;

        sstr << getAckUserData();

        // Split
        while (std::getline(sstr, tmp, '#'))
            tokens.push_back(tmp);

        for (auto &i : tokens) {
            sstr.str(i);

            int key;
            std::string name;
            int wins;
            int looses;
            int played;
            int ratio;
            bool loggedin;

            sstr >> tmp;
            key = boost::lexical_cast<int>(tmp);
            sstr >> name;
            sstr >> tmp;
            wins = boost::lexical_cast<int>(tmp);
            sstr >> tmp;
            looses = boost::lexical_cast<int>(tmp);
            sstr >> tmp;
            played = boost::lexical_cast<int>(tmp);
            sstr >> tmp;
            ratio = boost::lexical_cast<int>(tmp);
            sstr >> tmp;
            loggedin = boost::lexical_cast<bool>(tmp);

            std::shared_ptr<data::IPlayer> p(factory.getPlayer(name, ""));
            p->setAllData(key, wins, looses, played, ratio, loggedin);
            players[p->getKey()] = p;
        }
    }

    // ===============================================================

    bool TCPMessageUser::createQueryMessage(
        QUERY_MSG_TYPE_USER type,
        std::shared_ptr<data::IPlayer> p)
    {
        if (type == QUERY_MSG_TYPE_USER::NOT_SET)
            return false;

        // Set the query data
        std::string tmpQueryData;
        int typeInt = static_cast<int>(type);

        std::string tmpKey =  boost::lexical_cast<std::string>(p->getKey());
        std::string tmpName = p->getName();
        std::string tmpPw = p->getPassword();
        std::string tmpType = boost::lexical_cast<std::string>(typeInt);

        tmpQueryData = tmpType + ": " + tmpKey + " " + tmpName + " " + tmpPw;

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

        if (getAckUserData().length() != "")
            if (!parseAckUserData())
                return false;

        return true;
    }

    bool TCPMessageUser::setAckMessage(bool status)
    {
        std::string tmp;

        if (queryType == QUERY_MSG_TYPE_USER::NOT_SET)
            return false;

        ackType = static_cast<ACK_MSG_TYPE_USER>(queryType)

        int typeTmp = static_cast<int>(ackType);
        tmp = boost::lexical_cast<std::string>(typeTmp);

        if (status)
            tmp += ": SUCCESS";
        else
            tmp += ": FAILURE";

        return TCPMessage::setAckMessage(tmp);
    }

    bool TCPMessageUser::setAckMessage(
        std::map<int, std::shared_ptr<data::IPlayer>>& players)
    {
        std::string tmp;

        if (ackType == ACK_MSG_TYPE_USER::NOT_SET)
            return false;

        int typeTmp = static_cast<int>(ackType);
        tmp = boost::lexical_cast<std::string>(typeTmp);
        tmp += ":";

        for (auto& i : players) {
            tmp += " " + boost::lexical_cast<std::string>(i.second->getKey());
            tmp += " " + i.second->getName();
            tmp += " " + boost::lexical_cast<std::string>(i.second->getWins());
            tmp += " " + boost::lexical_cast<std::string>(i.second->getLooses());
            tmp += " " + boost::lexical_cast<std::string>(i.second->getPlayedGames());
            tmp += " " + boost::lexical_cast<std::string>(i.second->getWinRatio());
            tmp += " " + boost::lexical_cast<std::string>(i.second->isLoggedIn());
            tmp += "#";
        }

        return setAckMessage(tmp);
    }

    void TCPMessageUser::reset()
    {
        queryUser.reset();
        players.clear();
    }

    QUERY_MSG_TYPE_USER TCPMessageUser::getQueryType()
    {
        return queryType;
    }

    bool TCPMessageUser::getAckStatus()
    {
        return ackStatus;
    }

    std::map<int, std::shared_ptr<data::IPlayer>> TCPMessageUser::getPlayers()
    {
        return players;
    }

}
