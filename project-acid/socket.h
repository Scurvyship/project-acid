#pragma once
class Socket{
    public:
        Socket();
        ~Socket();

        void Send();

        int counter;
        bool bInit;
};

//extern Socket g_Socket;