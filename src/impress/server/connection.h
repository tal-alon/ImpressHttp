#pragma once

#include "../http/request.h"
#include "../logging/logger.h"
#include <WinSock2.h>
#include <string>

constexpr int CONNECTION_BUFFER_SIZE = 4096;


enum class SendStatus {
    IDLE,
    SEND
};


class Connection {
    SOCKET m_socket;
    Logger *m_logger;
    SendStatus m_send = SendStatus::IDLE;
    char m_buffer[CONNECTION_BUFFER_SIZE] = {};
    int m_buffer_size = 0;
    Request *m_waiting_request = nullptr;
    bool m_closed = false;

public:
    Connection(SOCKET socket, SendStatus send, Logger *logger);
    ~Connection();
    SOCKET sock_id() const;
    SendStatus send_status() const;
    void set_send_status(SendStatus status);
    SOCKET accept();
    void receive();
    void send(const char *data, int size);
    void set_waiting_request(Request *request);
    Request *get_waiting_request();
    void clear_waiting_request();
    char const *get_buffer() const;
    int get_buffer_size() const;
    char *try_pull_bytes(int size);
    char *try_pull_until(const std::string &delimiter);
    void close(bool force = false);
};
