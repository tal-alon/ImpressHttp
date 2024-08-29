#pragma once

#include <map>
#include <string>


class Headers {
    std::map<std::string, std::string> m_headers;

public:
    Headers();
    explicit Headers(const std::map<std::string, std::string> &headers);
    void set(const std::string &key, const std::string &value);
    const std::string &get(const std::string &key) const;
    const std::map<std::string, std::string> &map() const;
    std::string to_string() const;
    static Headers from_string(const std::string &raw);
};
