#include "socket.h"

Socket::Socket() {
    this->bInit = true;
}

Socket::~Socket() {

}

void Socket::Send() {
    this->counter++;
}

//Socket g_Socket;