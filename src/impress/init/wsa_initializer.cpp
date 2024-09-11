#include "wsa_initializer.h"

WSAInitializer::WSAInitializer() {
    if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        throw std::exception("Error at WSAStartup()");
    }
}

WSAInitializer::~WSAInitializer() {
    WSACleanup();
}
