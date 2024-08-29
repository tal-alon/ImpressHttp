#include "response.h"

#include <utility>

using namespace std;

Response::Response(string version, Status status, Headers headers, string body)
    : m_version(std::move(version)), m_status(status), m_headers(std::move(headers)), m_body(std::move(body)) {}

Response::Response(Status status) : m_status(status), m_version("HTTP/1.1") {}
Response::Response(Status status, std::string body) : m_status(status), m_version("HTTP/1.1"), m_body(std::move(body)) {}

const std::string &Response::version() const { return m_version; }
Status Response::status() const { return m_status; }
const Headers &Response::headers() const { return m_headers; }
const std::string &Response::body() const { return m_body; }
void Response::set_body(const string &body) { m_body = body; }

std::string Response::to_string() const {
    string response = m_version + " " + status_to_string(m_status) + "\r\n";
    for (auto &header : m_headers.map()) {
        response += header.first + ": " + header.second + "\r\n";
    }
    response += "\r\n";
    response += m_body;
    return response;
}
