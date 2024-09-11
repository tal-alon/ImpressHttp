#pragma once

#include <exception>
#include <string>


class SocketError : public std::exception {
    int m_error_code;
    std::string m_error_message;

public:
    explicit SocketError(std::string error_message);
    explicit SocketError(int error_code, std::string error_message);
    const char *what() const noexcept override;
    int getErrorCode() const;
};
