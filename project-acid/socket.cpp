#include "socket.h"

Socket::Socket() {
    // Init winsock
    printf("Winsock init...\n");
    this->iResult = WSAStartup(MAKEWORD(2,2), &this->wsaData);
    if(this->iResult != NO_ERROR) {
        printf("WSAStartup failed with error: %d\n", this->iResult);
        return;
    }
    printf("WSAStartup success!\n");

    // Spawn a socket
    this->SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(this->SendSocket == INVALID_SOCKET) {
        printf("Socket spawn failed with error: %ld\n", WSAGetLastError());
        WSACleanup();

        return;
    }

    // Setup some structures
    this->RecvAddr.sin_family = AF_INET;
    this->RecvAddr.sin_port = htons(PORT);
    this->RecvAddr.sin_addr.s_addr = inet_addr(IP);
}

Socket::~Socket() {
    closesocket(this->SendSocket);
    WSACleanup();
}

void Socket::Send(struct netdata_s netdata) {
    printf("sizeof netdata: %d", sizeof(struct netdata_s)); // 20
    char buffer[256];
    //memcpy_s(buffer, sizeof(netdata), &netdata, sizeof(netdata));
    memcpy(buffer, &netdata, sizeof(netdata));

    this->iResult = sendto(this->SendSocket, buffer, sizeof(buffer), 0, (SOCKADDR *)&this->RecvAddr, sizeof(this->RecvAddr));
    if(this->iResult == SOCKET_ERROR) {
        printf("Sendto failed, error: %d", WSAGetLastError());
    }
}