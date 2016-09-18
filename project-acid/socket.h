#pragma once
#include "DllMain.h"
#include <stdio.h>
#pragma comment(lib,"Ws2_32.lib") //Winsock Library

#define IP "127.0.0.1"
#define PORT 1337
#define BUFLEN 512

class Socket{
    public:
        Socket();
        ~Socket();

        void Send(struct netdata_s netdata);

    private:
        int iResult;
        WSADATA wsaData;

        SOCKET SendSocket = INVALID_SOCKET;
        sockaddr_in RecvAddr;

        WSADATA wsa;
};

//extern Socket g_Socket;