#include "connection.h"

using namespace std;


Connection::Connection(
        SOCKET socket,
        SendStatus send,
        Logger *logger) : m_socket(socket), m_send(send), m_logger(logger) {}

Connection::~Connection() {
    delete m_waiting_request;
    if (!m_closed) {
        close();
    }
}
SOCKET Connection::sock_id() const { return m_socket; }
SendStatus Connection::send_status() const { return m_send; }
bool Connection::is_closed() const { return m_closed; }

void Connection::receive() {
    if (m_closed) {
        m_logger->error("socket=" + to_string(m_socket) + " Attempted to receive on a closed socket");
        return;
    }

    char *buffer = m_buffer + m_buffer_size;
    int buffer_size = CONNECTION_BUFFER_SIZE - m_buffer_size;
    int bytes_recv = recv(m_socket, buffer, buffer_size, 0);
    if (bytes_recv == 0) {
        m_logger->info("socket=" + to_string(m_socket) + " Received an empty segment");
        close();
        return;
    }
    if (bytes_recv == SOCKET_ERROR) {
        m_logger->error("socket=" + to_string(m_socket) + " Failed to receive data");
        close(true);
        return;
    }
    m_buffer_size += bytes_recv;
    m_logger->info("socket=" + to_string(m_socket) + " Received " + to_string(bytes_recv) + " bytes");
}

void Connection::send(const char *data, int size) {
    if (m_closed) {
        m_logger->error("socket=" + to_string(m_socket) + " Attempted to send on a closed socket");
        return;
    }
    int bytes_sent = ::send(m_socket, data, size, 0);
    if (bytes_sent == SOCKET_ERROR) {
        m_logger->error("socket=" + to_string(m_socket) + " Failed to send data");
        close(true);
        return;
    }
    m_logger->info("socket=" + to_string(m_socket) + " Sent " + to_string(bytes_sent) + " bytes");
}

bool Connection::try_gather_request() {
    if (m_buffer_size == 0) {
        return false;
    }
    if (m_waiting_request != nullptr) {
        // TODO check if we have the whole body
        return false;
    }
    char *request_buff = try_pull_until("\r\n\r\n");
    if (request_buff == nullptr) {
        return false;
    }
    m_logger->info("socket=" + to_string(m_socket) + " Received request_buff");
    m_waiting_request = new Request(Request::from_string(request_buff));
    m_logger->info("Parsed request_buff: " + m_waiting_request->to_string());

    int content_length = m_waiting_request->content_length();
    if (content_length != 0) {
        auto body = try_pull_bytes(content_length);
        // TODO if body is nullptr, we should wait for more data
        if (body != nullptr) {
            m_waiting_request->set_body(body);
        }
    }
    // TODO only set the status to send if the request is complete
    // i.e. we have the whole body (body size == content length)
    m_send = SendStatus::SEND;
    return true;
}

Request *Connection::get_waiting_request() { return m_waiting_request; }
void Connection::clear_waiting_request() {
    delete m_waiting_request;
    m_waiting_request = nullptr;
    m_send = SendStatus::IDLE;
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
    char *result = new char[size + 1];
    memcpy(result, m_buffer, size);
    m_buffer_size -= size;
    memmove(m_buffer, m_buffer + size, m_buffer_size);
    result[size] = '\0';
    return result;
}

void Connection::close(bool force) {
    if (m_closed) {
        m_logger->info("socket=" + to_string(m_socket) + " Connection already closed");
        return;
    }
    if (!force) {
        m_logger->info("socket=" + to_string(m_socket) + " Closing connection");
    } else {
        int error = WSAGetLastError();
        m_logger->warn(
                "socket=" + to_string(m_socket) + " Forcing close connection" +
                ", error=" + to_string(error));
    }

    m_logger->info("socket=" + to_string(m_socket) + " Closing connection");

    m_closed = true;
    closesocket(m_socket);
}

// May not be super efficient, we check the whole buffer each time.
// Maybe we can save the last position we checked and start from there.
char *Connection::try_pull_until(const std::string &delimiter) {
    auto delimiter_size = (int) delimiter.size();

    for (int i = 0; i <= m_buffer_size - delimiter_size; i++) {
        if (memcmp(m_buffer + i, delimiter.c_str(), delimiter_size) == 0) {
            return try_pull_bytes(i + delimiter_size);
        }
    }
    return nullptr;
}
