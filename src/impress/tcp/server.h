#pragma once
#include <WinSock2.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

#include "../logging/logger.h"
#include "connection.h"


const int MAX_CONNECTIONS = 10;

class Server {
    Logger &m_logger;
    WSAData m_wsaData;
    const std::string &m_ip;
    int m_port;
    sockaddr_in m_address;
    SOCKET m_listen_sock;
    Connection m_connections[MAX_CONNECTIONS] = {};
    int m_client_count = 0;
    bool m_closed = false;//TODO - check if any bad stuff happens if we close the server twice

public:
    Server(const std::string &ip, int port, Logger &logger);
    ~Server();
    void run();
    void close();

private:
    void bind_socket();
    void exit_with_error(const std::string &message);
};
