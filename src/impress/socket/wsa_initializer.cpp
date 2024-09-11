#include "wsa_initializer.h"

#include "./socket_error.h"

WSAInitializer::WSAInitializer() {
    if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        throw SocketError("Error at WSAStartup()");
    }
}

WSAInitializer::~WSAInitializer() {
    WSACleanup();
}
