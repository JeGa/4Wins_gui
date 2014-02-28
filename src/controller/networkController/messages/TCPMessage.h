/*
* Messages are used to encapsulate the TCP data to send over
* the network. They provide a abstraction for the different commands
* and are easier to use as rare data.
*
*
* There are two types of messages: QUERY and ACK
* All messages require a QUERY/ACK message pair:
*
* QUERY:
* Is sent to the other side to query for data and information.
*
* ACK:
* Is the acknowledgement for a QUERY message. A ACK message
* contains the data from the QUERY and the acknowledge data.
*
* Each QUERY/ACK pair has a sender-unique identifier. One exception
* is the keep alive message. For that there is no QUERY/ACK needed.
*
*
* A message is constructed as internalData string:
* [[HEADER] [MSG_KEY] [TYPE] [QUERY_USER_DATA] [ACK_USER_DATA] [FOOTER]]
*/

#ifndef TCPMESSAGE_H
#define TCPMESSAGE_H

#include <string>

namespace controller
{

    enum class MSG_TYPE
    {
        NOT_SET = 0, UNDEF = 1, KEEP_ALIVE = 2, QUERY = 3, ACK = 4
    };

    class TCPMessage
    {
        private:
            // Unique identifier counter
            static int msgKeyCounter;

            static const std::string HEADER;
            static const std::string FOOTER;
            static const std::string KEEP_ALIVE_MESSAGE;

            int msgKey = -1;
            MSG_TYPE type = MSG_TYPE::NOT_SET;

            // What the client sends
            std::string queryUserData = "";
            // What the server sends back
            std::string ackUserData = "";

            // If this message has valid data
            bool valid = false;

            // The send string with the frame (client and server data)
            std::string internalData = "";

            // Fills the internal data variable.
            void buildFrameData();
            bool parseFrameData(std::string data);

        public:
            TCPMessage() {}
            virtual ~TCPMessage() {}

            /* FOR QUERY SEND:
             *
             * Sets queryUserData to send it to the receiver. The data
             * string is encapsulated with the TCPMessage frame.
             *
             * Message must be a new message (or reset() is needed).
             */
            virtual bool createQueryMessage(std::string data);

            /* FOR ANY MESSAGE RECEIVE:
             *
             * Create message based on a frame data string.
             */
            virtual bool createMessage(std::string frameData);

            /* FOR ACK SEND:
             *
             * Sets the ackUserData to send back to the sender.
             *
             * Message must be a QUERY message.
             */
            virtual bool setAckMessage(std::string data);

            /*
             * This resets the message to create a new message. Normally the user
             * is prevented from creating a new message if the object is already
             * a valid message (to prevent loss of message information).
             */
            virtual void reset();

            bool createKeepAliveMessage();

            bool isValid();

            MSG_TYPE getType();
            std::string getFrameData();
            std::string getQueryUserData();
            std::string getAckUserData();
            int getMsgKey();

            std::string toString();
    };

}

#endif // TCPMESSAGE_H
