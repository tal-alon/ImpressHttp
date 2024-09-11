#pragma once

#include <map>
#include <string>


class Headers {
    std::map<std::string, std::string> m_headers;

public:
    Headers();
    explicit Headers(const std::map<std::string, std::string> &headers);
    bool has(const std::string &key) const;
    std::string *operator[](const std::string &key);
    const std::string *operator[](const std::string &key) const;
    std::string to_string() const;
    static Headers from_string(const std::string &raw);
    std::map<std::string, std::string>::const_iterator begin() const;
    std::map<std::string, std::string>::const_iterator end() const;
};
