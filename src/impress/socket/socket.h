#ifndef NETWORKS_EX1_SOCKET_H
#define NETWORKS_EX1_SOCKET_H

#include <WinSock2.h>

class Socket {
    SOCKET m_socket;

public:
    Socket(int af, int type, int protocol);
    ~Socket();
    void set_unblocking();
    SOCKET descriptor() const;
};


#endif//NETWORKS_EX1_SOCKET_H
