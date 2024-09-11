#pragma once

#include "headers.h"
#include "status.h"


class Response {
    std::string m_version;
    Status m_status;
    Headers m_headers;
    std::string m_body;

public:
    Response(
            std::string version,
            Status status,
            Headers headers,
            std::string body);
    Response(Status status);
    Response(Status status, std::string body);
    const std::string &version() const;
    Status status() const;
    const Headers &headers() const;
    const std::string &body() const;
    void set_body(const std::string &body);
    std::string to_string() const;
    static Response from_string(const std::string &raw);
};
