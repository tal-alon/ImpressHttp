#include "connection.h"

Connection::Connection(
        SOCKET socket,
        ReceiveStatus receive,
        SendStatus send
        ) : m_socket(socket), m_receive(receive), m_send(send) {}

Connection::~Connection() {
    close();
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
char *Connection::pull_from_buffer(int size) {
    if (size > m_buffer_size) {
        return nullptr;
    }
    char *result = new char[size];
    memcpy(result, m_buffer, size);
    m_buffer_size -= size;
    memmove(m_buffer, m_buffer + size, m_buffer_size);
    return result;
}

void Connection::close() {
    if (m_closed) {
        return;
    }
    m_closed = true;
    closesocket(m_socket);
}
