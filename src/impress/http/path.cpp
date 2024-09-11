#include "path.h"

#include <sstream>
#include <utility>

using namespace std;

Path::Path(string url, QueryParams params) : m_url(std::move(url)), m_params(std::move(params)) {}

const string &Path::url() const { return m_url; }

const QueryParams &Path::params() const { return m_params; }

const string &Path::get_param(const string &key) const {
    return m_params.at(key);// TODO - handle missing key
}

string Path::to_string() const {
    ostringstream stream;

    if (m_url.empty()) {
        return "";
    }

    stream << m_url << "?";
    for (const auto &pair : m_params) {
        stream << pair.first << "=" << pair.second << "&";
    }
    stream << '\b';// remove the last '&'

    return stream.str();
}

Path Path::from_string(const string &raw) {
    size_t pos = raw.find('?');

    if (pos == string::npos) {
        return {raw, {}};
    }

    string url = raw.substr(0, pos);
    string raw_params = raw.substr(pos + 1);
    QueryParams params = parse_params(raw_params);
    return {url, params};
}

QueryParams Path::parse_params(const string &raw_params) {
    QueryParams params;
    istringstream stream(raw_params);
    string pair;

    while (getline(stream, pair, '&')) {
        size_t pos = pair.find('=');
        if (pos != std::string::npos) {
            string key = pair.substr(0, pos);
            string value = pair.substr(pos + 1);
            params[key] = value;
        } else {// if there is no value, set it to an empty string
            params[pair] = "";
        }
    }
    return params;
}
