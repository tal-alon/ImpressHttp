#include "server.h"

#include <utility>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;

Server::Server(string ip, int port, Logger &logger) : m_ip(std::move(ip)), m_port(port), m_logger(logger) {
    // Initialize the address
    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(m_port);
    m_address.sin_addr.s_addr = inet_addr(m_ip.c_str());

    // Initialize the Winsock library
    if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &m_wsaData)) {
        exit_with_error("Error at WSAStartup()");
    }

    // Create the listening socket
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
        update_fd_sets();
        handle_recv_and_send();

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

void Server::update_fd_sets() {
    FD_ZERO(&m_wait_recv);
    FD_ZERO(&m_wait_send);
    for (int i = 0; i < m_client_count; i++) {
        FD_SET(m_connections[i]->sock_id(), &m_wait_recv);
        if (m_connections[i]->send_status() == SendStatus::SEND) {
            FD_SET(m_connections[i]->sock_id(), &m_wait_send);
        }
    }
}

void Server::accept_new_connection() {
    if (MAX_CONNECTIONS <= m_client_count) {
        m_logger.warn("Max number of connections reached, closing new connection");
        return;
    }

    SOCKET client_socket = accept(m_listen_sock, nullptr, nullptr);
    if (INVALID_SOCKET == client_socket) {
        exit_with_error("Error at accept()");
    }

    m_logger.info(
            "Accepted new connection, socket=" + to_string(client_socket) +
            ", client_count=" + to_string(m_client_count)
            );
    m_connections[m_client_count] = new Connection(client_socket, ReceiveStatus::RECEIVE, SendStatus::IDLE, m_logger);
    m_client_count++;
}

void Server::remove_connection(int index) {
    m_logger.info("Removing connection, socket=" + to_string(m_connections[index]->sock_id()));
    delete m_connections[index];
    m_connections[index] = m_connections[m_client_count - 1];
    m_client_count--;
}

void Server::handle_recv_and_send() {
    int n_ready = select(0, &m_wait_recv, &m_wait_send, nullptr, nullptr);
    if (n_ready == SOCKET_ERROR) {
        exit_with_error("Error at select()");
    }

    if (FD_ISSET(m_listen_sock, &m_wait_recv)) {
        accept_new_connection();
    }

    // TODO - change this behavior
    for (int i = 0; i < m_client_count && 0 < n_ready; i++) {
        if (FD_ISSET(m_connections[i]->sock_id(), &m_wait_recv)) {
            m_connections[i]->receive();
            n_ready--;
        }
    }
    for (int i = 0; i < m_client_count && 0 < n_ready; i++) {
        if (FD_ISSET(m_connections[i]->sock_id(), &m_wait_send)) {
            m_connections[i]->send("Hello, client!", 14);
            n_ready--;
        }
    }
}
void Server::check_for_completed_requests() {
    for (int i = 0; i < m_client_count; i++) {
        if (m_connections[i]->get_buffer_size() == 0) {
            continue;
        }
        char *request = m_connections[i]->try_pull_until("\r\n\r\n");
        if (request == nullptr) {
            continue;
        }
        m_logger.info("Received request, socket=" + to_string(m_connections[i]->sock_id()));
        auto http_request = Request::from_string(request);
        m_logger.info("Parsed request: + " + http_request.to_string());
        handle_request(http_request, *m_connections[i]);
    }
}
void Server::handle_request(Request &request, Connection &connection) {
    m_logger.info("Handling request: " + request.to_string());
    // TODO - update the connection buffer and status
}
