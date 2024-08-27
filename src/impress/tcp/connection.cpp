#include "connection.h"

using namespace std;


Connection::Connection(
        SOCKET socket,
        ReceiveStatus receive,
        SendStatus send,
        Logger &logger) : m_socket(socket), m_receive(receive), m_send(send), m_logger(logger) {}

Connection::~Connection() {
    close();
}

SOCKET Connection::accept() {
    if (m_closed) {
        m_logger.error("Attempted to accept on a closed socket, socket=" + to_string(m_socket));
        return INVALID_SOCKET;
    }
    SOCKET client_socket = ::accept(m_socket, nullptr, nullptr);
    if (client_socket == INVALID_SOCKET) {
        m_logger.error("Failed to accept connection, socket=" + to_string(m_socket));
        close(true);
        return INVALID_SOCKET;
    }
    m_logger.info("Accepted new connection, socket=" + to_string(client_socket));
    return client_socket;
}

void Connection::receive() {
    if (m_closed) {
        m_logger.error("Attempted to receive on a closed socket, socket=" + to_string(m_socket));
        return;
    }

    char *buffer = m_buffer + m_buffer_size;
    int buffer_size = CONNECTION_BUFFER_SIZE - m_buffer_size;
    int bytes_recv = recv(m_socket, buffer, buffer_size, 0);
    if (bytes_recv == 0) {
        m_logger.info("Received an empty segment, socket=" + to_string(m_socket));
        close();
        return;
    }
    if (bytes_recv == SOCKET_ERROR) {
        m_logger.error("Failed to receive data, socket=" + to_string(m_socket));
        close(true);
        return;
    }
    m_buffer_size += bytes_recv;
    m_logger.info("Received " + to_string(bytes_recv) + " bytes, socket=" + to_string(m_socket));
}

void Connection::send(const char *data, int size) {
    if (m_closed) {
        m_logger.error("Attempted to send on a closed socket, socket=" + to_string(m_socket));
        return;
    }
    int bytes_sent = ::send(m_socket, data, size, 0);
    if (bytes_sent == SOCKET_ERROR) {
        m_logger.error("Failed to send data, socket=" + to_string(m_socket));
        close(true);
        return;
    }
    m_logger.info("Sent " + to_string(bytes_sent) + " bytes, socket=" + to_string(m_socket));
}

char const *Connection::get_buffer() const {
    return m_buffer;
}

int Connection::get_buffer_size() const {
    return m_buffer_size;
}


/// \brief Receive data from the socket buffer
/// \param size
/// \return dynamically allocated buffer with the received data
char *Connection::try_pull_bytes(int size) {
    if (size > m_buffer_size) {
        return nullptr;
    }
    char *result = new char[size];
    memcpy(result, m_buffer, size);
    m_buffer_size -= size;
    memmove(m_buffer, m_buffer + size, m_buffer_size);
    return result;
}

void Connection::close(bool force) {
    if (m_closed) {
        m_logger.info("Connection already closed, socket=" + to_string(m_socket));
        return;
    }
    if (!force) {
        m_logger.info("Closing connection, socket=" + to_string(m_socket));
    } else {
        int error = WSAGetLastError();
        m_logger.warn(
                "Forcing close connection, socket=" + to_string(m_socket) +
                ", error=" + to_string(error));
    }

    m_closed = true;
    closesocket(m_socket);
}

// May not be super efficient, we check the whole buffer each time.
// Maybe we can save the last position we checked and start from there.
char *Connection::try_pull_until(const std::string &delimiter) {
    auto delimiter_size = (int) delimiter.size();

    for (int i = 0; i < m_buffer_size - delimiter_size; i++) {
        if (memcmp(m_buffer + i, delimiter.c_str(), delimiter_size) == 0) {
            return try_pull_bytes(i + delimiter_size);
        }
    }
    return nullptr;
}
