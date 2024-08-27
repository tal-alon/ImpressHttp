#include "server.h"

#include <utility>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;

Server::Server(string ip, int port, Logger &logger) : m_ip(std::move(ip)), m_port(port), m_logger(logger) {
    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(m_port);
    m_address.sin_addr.s_addr = inet_addr(m_ip.c_str());

    if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &m_wsaData)) {
        exit_with_error("Error at WSAStartup()");
    }

    m_listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == m_listen_sock) {
        exit_with_error("Error at socket()");
    }
}

Server::~Server() {
    close();
}


void Server::run() {
    m_logger.info("Server is running on " + m_ip + ":" + to_string(m_port));
    bind_socket();
    while (true) {
    }
}

void Server::close() {
    // Check if the server is already closed
    if (m_closed) {
        return;
    }
    m_closed = true;
    closesocket(m_listen_sock);
    WSACleanup();
}


void Server::bind_socket() {
    if (SOCKET_ERROR == bind(m_listen_sock, (sockaddr *) &m_address, sizeof(m_address))) {
        exit_with_error("Error at bind()");
    }
}

void Server::exit_with_error(const string &message) {
    int error_code = WSAGetLastError();
    m_logger.error(message + " " + to_string(error_code));

    close();
    exit(EXIT_FAILURE);
}
