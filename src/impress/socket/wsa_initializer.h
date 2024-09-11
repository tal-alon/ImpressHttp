#ifndef NETWORKS_EX1_WSAINITIALIZER_H
#define NETWORKS_EX1_WSAINITIALIZER_H

#include <WinSock2.h>
#include <iostream>


class WSAInitializer {
    WSAData m_wsaData;

public:
    WSAInitializer();
    ~WSAInitializer();

    const WSAData &getWSAData() const {
        return this->m_wsaData;
    }
};


#endif//NETWORKS_EX1_WSAINITIALIZER_H
