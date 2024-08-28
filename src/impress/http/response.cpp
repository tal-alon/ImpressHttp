#include "response.h"

#include <utility>

using namespace std;

Response::Response(string version, Status status, Headers headers, string body)
    : m_version(std::move(version)), m_status(status), m_headers(std::move(headers)), m_body(std::move(body)) {}

Response::Response(Status status) : m_status(status), m_version("HTTP/1.1") {}
Response::Response(Status status, std::string body) : m_status(status), m_version("HTTP/1.1"), m_body(std::move(body)) {}
