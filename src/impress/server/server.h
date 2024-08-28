#pragma once
#include <WinSock2.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

#include "../logging/logger.h"
#include "../http/request.h"
#include "connection.h"
#include "router.h"


const int MAX_CONNECTIONS = 10;

class Server {
    Router m_router;
    Logger &m_logger;
    WSAData m_wsaData;
    std::string m_ip;
    int m_port;
    sockaddr_in m_address;
    SOCKET m_listen_sock;
    Connection *m_connections[MAX_CONNECTIONS];
    fd_set m_wait_recv, m_wait_send;
    int m_client_count = 0;
    bool m_closed = false;//TODO - check if any bad stuff happens if we close the server twice

public:
    Server(std::string ip, int port, Logger &logger);
    ~Server();
    void set_router(Router router);
    [[noreturn]] void run();
    void close();

private:
    void bind_socket();
    void exit_with_error(const std::string &message);
    void update_fd_sets();
    void accept_new_connection();
    void remove_connection(int index);
    void handle_recv_and_send();
    void check_for_completed_requests();
    void handle_request(Request &request, Connection &connection);
};
