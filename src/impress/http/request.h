#pragma once
#include "./method.h"
#include <map>
#include <string>


class Request {
    std::string m_raw;
    Method m_method;
    std::string m_path;
    std::string m_version;
    std::string m_body;
    std::map<std::string, std::string> m_headers;

public:
    Request(
            std::string &raw,
            Method method,
            std::string &path,
            std::string &version,
            std::string &body,
            std::map<std::string, std::string> &headers);
    const std::string &raw() const;
    Method method() const;
    const std::string &path() const;
    const std::string &version() const;
    const std::string &body() const;
    const std::map<std::string, std::string> &headers() const;
    std::string to_string() const;
    static Request from_string(const std::string &request);
};
