#include "server.h"

#include <utility>

#include "../logging/dummy_logger.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;

Server::Server(string ip, int port, Logger *logger) :
        m_ip(std::move(ip)),
        m_port(port),
        m_listen_sock(AF_INET, SOCK_STREAM, IPPROTO_TCP) {

    // Initialize the address
    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(m_port);
    m_address.sin_addr.s_addr = inet_addr(m_ip.c_str());

    set_logger(logger);
}

Server::Server(std::string ip, int port) : Server(std::move(ip), port, new DummyLogger()) {}

Server::~Server() {
    delete m_logger;
    for (int i = 0; i < m_client_count; i++) {
        delete m_connections[i];
    }
}

Router &Server::router() {
    return m_router;
}

void Server::set_router(Router router) {
    m_router = std::move(router);
}

void Server::set_logger(Logger *logger) {
    if (logger == nullptr) {
        m_logger = new DummyLogger();
    } else {
        m_logger = logger;
    }
}

void Server::run() {
    m_logger->info("Server is running on " + m_ip + ":" + to_string(m_port));
    bind_socket();

    while (true) {
        update_fd_sets();
        handle_recv_and_send();
    }
}


void Server::bind_socket() {
    SOCKET sock_id = m_listen_sock.descriptor();
    if (SOCKET_ERROR == bind(sock_id, (sockaddr *) &m_address, sizeof(m_address))) {
        exit_with_error("Error at bind()");
    }
}

void Server::exit_with_error(const string &message) {
    int error_code = WSAGetLastError();
    m_logger->error(message + " " + to_string(error_code));

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
        m_logger->warn("Max number of connections reached, closing new connection");
        return;
    }
    SOCKET client_socket = accept(m_listen_sock.descriptor(), nullptr, nullptr);
    if (INVALID_SOCKET == client_socket) {
        exit_with_error("Error at accept()");
    }

    m_logger->info(
            "Accepted new connection, socket=" + to_string(client_socket) +
            ", client_count=" + to_string(m_client_count));
    m_connections[m_client_count] = new Connection(client_socket, SendStatus::IDLE, m_logger);
    m_client_count++;
}

void Server::remove_connection(int index) {
    m_logger->info("Removing connection, socket=" + to_string(m_connections[index]->sock_id()));
    delete m_connections[index];
    m_connections[index] = m_connections[m_client_count - 1];
    m_client_count--;
}

void Server::handle_recv_and_send() {
    int n_ready = select(0, &m_wait_recv, &m_wait_send, nullptr, nullptr);
    if (n_ready == SOCKET_ERROR) {
        exit_with_error("Error at select()");
    }

    if (FD_ISSET(m_listen_sock.descriptor(), &m_wait_recv)) {
        accept_new_connection();
    }

    for (int i = 0; i < m_client_count && 0 < n_ready; i++) {
        if (FD_ISSET(m_connections[i]->sock_id(), &m_wait_recv)) {
            m_connections[i]->receive();
            n_ready--;
        }
    }
    for (int i = 0; i < m_client_count && 0 < n_ready; i++) {
        if (FD_ISSET(m_connections[i]->sock_id(), &m_wait_send)) {
            handle_completed_request(i);
            n_ready--;
        }
    }
    check_for_completed_requests();
}

void Server::check_for_completed_requests() {
    for (int i = 0; i < m_client_count; i++) {
        if (m_connections[i]->get_waiting_request() != nullptr) {
            continue;
        }
        if (m_connections[i]->get_buffer_size() == 0) {
            continue;
        }
        char *request = m_connections[i]->try_pull_until("\r\n\r\n");
        if (request == nullptr) {
            continue;
        }
        m_logger->info("Received request, socket=" + to_string(m_connections[i]->sock_id()));
        auto http_request = new Request(Request::from_string(request));
        m_logger->info("Parsed request: + " + http_request->to_string());
        m_connections[i]->set_waiting_request(http_request);
        auto content_length = atoi(http_request->get_header("Content-Length").c_str());
        if (content_length != 0) {
            auto body = m_connections[i]->try_pull_bytes(content_length);
            if (body != nullptr) {
                http_request->set_body(body);
            }
        }
        m_connections[i]->set_send_status(SendStatus::SEND);
    }
}
void Server::handle_completed_request(int connection_index) {
    Connection &connection = *m_connections[connection_index];
    auto request = connection.get_waiting_request();
    auto response = m_router.handle_request(*request);
    auto res_string = response.to_string();
    auto buffer = res_string.c_str();
    auto buffer_size = (int) res_string.size();
    connection.send(buffer, buffer_size);
    connection.clear_waiting_request();
}
