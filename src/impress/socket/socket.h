#ifndef NETWORKS_EX1_SOCKET_H
#define NETWORKS_EX1_SOCKET_H

#include <WinSock2.h>

class Socket {
    SOCKET connSocket;

public:
    Socket(int af, int type, int protocol);
    ~Socket();
    SOCKET descriptor() const;
};


#endif//NETWORKS_EX1_SOCKET_H
