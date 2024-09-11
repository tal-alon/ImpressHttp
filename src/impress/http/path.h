#pragma once

#include <map>
#include <string>

typedef std::map<std::string, std::string> QueryParams;


class Path {
    std::string m_url;
    QueryParams m_params;

public:
    Path(std::string url, QueryParams params);
    const std::string &url() const;
    const QueryParams &params() const;
    const std::string &get_param(const std::string &key) const;
    std::string to_string() const;
    static Path from_string(const std::string &raw);

private:
    static QueryParams parse_params(const std::string &raw_params);
};
