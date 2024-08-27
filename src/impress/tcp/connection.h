#pragma once

#include <WinSock2.h>

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
    ReceiveStatus m_receive = ReceiveStatus::LISTEN;
    SendStatus m_send = SendStatus::IDLE;
    char m_buffer[CONNECTION_BUFFER_SIZE] = {};
    int m_buffer_size = 0;
    bool m_closed = false;

public:
    Connection(SOCKET socket, ReceiveStatus receive, SendStatus send);
    ~Connection();
    void receive();
    void send(const char *data, int size);
    char const *get_buffer() const;
    int get_buffer_size() const;
    char *pull_from_buffer(int size);
    void close();
};
