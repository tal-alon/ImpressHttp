#pragma once

#include "./headers.h"
#include <string>
#include <vector>


class Message {
protected:
    std::string m_version;
    Headers m_headers;
    std::vector<char> m_body;

public:
    Message(std::string version,
            Headers headers,
            const std::vector<char>& body);
    Message(std::string version,
            Headers headers);
    Message(std::string version,
            const std::vector<char>& body);
    explicit Message(std::string version);
    const std::string &version() const;
    const std::vector<char> &body() const;
    const Headers &headers() const;
    void set_body(const std::vector<char> &body);
    void set_body(char *body, size_t size);
    const std::string *get_header(const std::string &key) const;
};
