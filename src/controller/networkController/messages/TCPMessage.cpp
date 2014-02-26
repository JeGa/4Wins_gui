#include "TCPMessage.h"
#include <sstream>
#include <vector>
#include <cstdlib>
#include <boost/lexical_cast.hpp>

namespace controller
{

    const std::string TCPMessage::HEADER = "4WINS HEADER";
    const std::string TCPMessage::FOOTER = "4WINS FOOTER";
    const std::string TCPMessage::KEEP_ALIVE_MESSAGE = "4WINS ALIVE";
    int TCPMessage::msgKeyCounter = 0;

    TCPMessage::TCPMessage()
    {
    }

    // Create and format the string to send over the network.
    void TCPMessage::buildFrameData()
    {
        std::string frameData = "";
        std::stringstream sstr;

        sstr << static_cast<int>(msgKey);
        frameData = HEADER + ";" + sstr.str() + ";";
        sstr.str("");

        sstr << static_cast<int>(type);
        frameData += sstr.str() + ";" + queryUserData + ";" +
                     ackUserData + ";" + FOOTER;

        internalData = frameData;
    }

    // Creates this message object based on a message received from the other
    // socket (encapsulated with the TCPMessage frame).
    bool TCPMessage::parseFrameData(std::string data)
    {
        std::stringstream sstr;
        std::string tmp = "";
        std::vector<std::string> tokens;

        sstr << data;

        // Split by ';'
        while (std::getline(sstr, tmp, ';'))
            tokens.push_back(tmp);
        sstr.str("");

        if (tokens.size() != 6)
            return false;

        // Check Header
        if (tokens[0] != HEADER)
            return false;

        // Check Footer
        if (tokens[5] != FOOTER)
            return false;

        // Set msgKey
        tmp = tokens[1];
        int tmpKey = atoi(tmp.c_str());
        msgKey = tmpKey;

        // Set type
        tmp = tokens[2];
        int tmpInt = atoi(tmp.c_str());
        MSG_TYPE tmpType = static_cast<MSG_TYPE>(tmpInt);
        type = tmpType;

        // Set query data
        std::string tmpQuery = tokens[3];

        // Set ack data
        std::string tmpAck = tokens[4];

        if (tmpQuery.length() == 0)
            return false;
        queryUserData = tmpQuery;
        ackUserData = tmpAck;

        // Remove '\n'
//		tmp.erase(tmp.length()-1);

        return true;
    }

    // =========================================================================

    bool TCPMessage::createQueryMessage(std::string data)
    {
        valid = false;

        // Message must be new.
        if (type != MSG_TYPE::NOT_SET)
            return false;

        if (data.length() == 0)
            return false;

        queryUserData = data;
        type = MSG_TYPE::QUERY;

        msgKey = msgKeyCounter;
        msgKeyCounter++;

        buildFrameData();
        valid = true;
        return valid;
    }

    bool TCPMessage::createMessage(std::string frameData)
    {
        valid = false;

        if (type != MSG_TYPE::NOT_SET)
            return false;

        if (!parseFrameData(frameData))
            return false;

        buildFrameData();
        valid = true;
        return valid;
    }

    bool TCPMessage::setAckMessage(std::string data)
    {
        valid = false;

        if (type != MSG_TYPE::QUERY)
            return false;

        if (data.length() == 0)
            return false;

        ackUserData = data;

        type = MSG_TYPE::ACK;

        buildFrameData();
        valid = true;
        return valid;
    }

    bool TCPMessage::createKeepAliveMessage()
    {
        valid = false;

        if (type != MSG_TYPE::NOT_SET)
            return false;

        type = MSG_TYPE::KEEP_ALIVE;
        queryUserData = KEEP_ALIVE_MESSAGE;

        buildFrameData();
        valid = true;
        return valid;
    }

    // =========================================================================

    MSG_TYPE TCPMessage::getType()
    {
        return type;
    }

    std::string TCPMessage::getFrameData()
    {
        return this->internalData;
    }

    std::string TCPMessage::getQueryUserData()
    {
        return this->queryUserData;
    }

    std::string TCPMessage::getAckUserData()
    {
        return this->ackUserData;
    }

    int TCPMessage::getMsgKey()
    {
        return msgKey;
    }

    bool TCPMessage::isValid()
    {
        return valid;
    }

    void TCPMessage::reset()
    {
        type = MSG_TYPE::NOT_SET;
        queryUserData = "";
        ackUserData = "";
        internalData = "";
        msgKey = -1;
        valid = false;
    }

    std::string TCPMessage::toString()
    {
        std::string str;
        int typeInt = static_cast<int>(type);

        str = "==========================\n";
        str += "Message key: " + boost::lexical_cast<std::string>(msgKey) + " \n";
        str += "Type: " + boost::lexical_cast<std::string>(typeInt) + " \n";
        str += "Valid: " + boost::lexical_cast<std::string>(valid) + " \n";
        str += "Query User Data: " + queryUserData + " \n";
        str += "Ack User Data: " + ackUserData + " \n";
        str += "Internal Data: " + internalData + " \n";

        return str;
    }

}
