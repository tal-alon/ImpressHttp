#include "socket.h"

#include "./socket_error.h"

using namespace std;

Socket::Socket(int af, int type, int protocol) {
    m_socket = socket(af, type, protocol);
    if (INVALID_SOCKET == m_socket) {
        throw SocketError("Error at socket(): ");
    }
}

Socket::~Socket() {
    closesocket(m_socket);
}

void Socket::set_unblocking() {
    unsigned long flag=1;
    if (ioctlsocket(m_socket, FIONBIO, &flag) != 0) {
        throw SocketError("socket:" + to_string(m_socket) + "Error at ioctlsocket()");
    }
}

SOCKET Socket::descriptor() const {
    return m_socket;
}
