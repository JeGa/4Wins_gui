#ifndef IUSERINTERFACE_H
#define IUSERINTERFACE_H

namespace view
{

    class IUserInterface
    {
    public:
        IUserInterface() {};
        virtual ~IUserInterface() {};      
        
        virtual void run() = 0;
    };

}

#endif // IUSERINTERFACE_H
