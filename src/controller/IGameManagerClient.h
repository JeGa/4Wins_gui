#ifndef IGAMEMANAGERCLIENT_H
#define IGAMEMANAGERCLIENT_H

#include "IGame.h"
#include "AGameManager.h"

namespace controller
{
    
    class IGameManagerClient : public AGameManager
    {
    public:
        virtual ~IGameManagerClient() {};
        
        virtual bool login() = 0;
        virtual bool logout() = 0;
        virtual bool registerUser(std::string name, std::string pw) = 0;
        virtual bool ping() = 0;
        
        virtual void newGame(data::IGame *game) = 0;
        virtual bool deleteGame(data::IGame *game) = 0;
        virtual bool input(int x, int y) = 0;
    };
    
}

#endif