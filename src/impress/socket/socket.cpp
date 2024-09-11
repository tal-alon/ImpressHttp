#include "socket.h"

#include "./socket_error.h"

using namespace std;

Socket::Socket(int af, int type, int protocol) {
    this->connSocket = socket(af, type, protocol);
    if (INVALID_SOCKET == this->connSocket) {
        throw SocketError("Error at socket(): ");
    }
}

Socket::~Socket() {
    closesocket(this->connSocket);
}

SOCKET Socket::descriptor() const {
    return this->connSocket;
}
