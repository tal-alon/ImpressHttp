#pragma once

#include <WinSock2.h>
#include <string>
#include "../logging/logger.h"

constexpr int CONNECTION_BUFFER_SIZE = 4096;

enum class ReceiveStatus {
    LISTEN,
    RECEIVE
};

enum class SendStatus {
    IDLE,
    SEND
};


class Connection {
    SOCKET m_socket;
    Logger &m_logger;
    ReceiveStatus m_receive = ReceiveStatus::LISTEN; // TODO - do we need this?
    SendStatus m_send = SendStatus::IDLE;
    char m_buffer[CONNECTION_BUFFER_SIZE] = {};
    int m_buffer_size = 0;
    bool m_closed = false;

public:
    Connection(SOCKET socket, ReceiveStatus receive, SendStatus send, Logger &logger);
    ~Connection();
    SOCKET sock_id() const;
    SendStatus send_status() const;
    SOCKET accept();
    void receive();
    void send(const char *data, int size);
    char const *get_buffer() const;
    int get_buffer_size() const;
    char *try_pull_bytes(int size);
    char *try_pull_until(const std::string &delimiter);
    void close(bool force = false);
};
