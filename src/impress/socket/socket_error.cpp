#include "socket_error.h"

#include <WinSock2.h>

using namespace std;

SocketError::SocketError(string error_message) {
    this->m_error_code = WSAGetLastError();
    this->m_error_message = std::move(error_message) + ", WSA error code: " + to_string(this->m_error_code);
}

SocketError::SocketError(int error_code, std::string error_message) {
    this->m_error_code = error_code;
    this->m_error_message = std::move(error_message) + ", WSA error code: " + to_string(this->m_error_code);
}

const char *SocketError::what() const noexcept {
    return this->m_error_message.c_str();
}

int SocketError::getErrorCode() const {
    return this->m_error_code;
}
