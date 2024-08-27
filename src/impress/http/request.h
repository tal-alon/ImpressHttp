#pragma once
#include "./method.h"
#include <map>
#include <string>

#define CRLF "\r\n"

typedef std::map<std::string, std::string> Headers;


class Request {
    Method m_method;
    std::string m_path;
    std::string m_version;
    std::string m_body;
    Headers m_headers;

public:
    Request(
            Method method,
            std::string &path,
            std::string &version,
            std::string &body,
            Headers &headers);
    Method method() const;
    const std::string &path() const;
    const std::string &version() const;
    const std::string &body() const;
    void set_body(const std::string &body);
    const std::map<std::string, std::string> &headers() const;
    std::string to_string() const;
    static Request from_string(const std::string &raw);

private:
    static void parse_request_line(const std::string &line, Method &method, std::string &path, std::string &version);
    static Headers parse_headers(const std::string &raw_header);
};
