#include "wsa_initializer.h"

#include "./socket_error.h"
#pragma comment(lib, "Ws2_32.lib")

WSAInitializer::WSAInitializer() {
    if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &m_wsaData)) {
        throw SocketError("Error at WSAStartup()");
    }
}

WSAInitializer::~WSAInitializer() {
    WSACleanup();
}
