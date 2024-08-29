#pragma once
#include <map>
#include <string>
#include "./method.h"
#include "./path.h"
#include "./headers.h"

#define CRLF "\r\n"


class Request {
    Method m_method;
    Path m_path;
    std::string m_version;
    std::string m_body;
    Headers m_headers;

public:
    Request(
            Method method,
            Path &path,
            std::string &version,
            std::string &body,
            Headers &headers);
    Method method() const;
    const Path &path() const;
    const QueryParams &query_params() const;
    const std::string &version() const;
    const std::string &body() const;
    void set_body(const std::string &body);
    const Headers &headers() const;
    const std::string &get_header(const std::string &key) const;
    std::string to_string() const;
    static Request from_string(const std::string &raw);

private:
    static void parse_request_line(const std::string &line, Method &method, std::string &path, std::string &version);
};
