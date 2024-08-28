#include "response.h"

#include <utility>

using namespace std;

Response::Response(string version, Status status, Headers headers, string body)
    : m_version(std::move(version)), m_status(status), m_headers(std::move(headers)), m_body(std::move(body)) {}