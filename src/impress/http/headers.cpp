#include "headers.h"

#include <sstream>

using namespace std;

Headers::Headers() = default;

Headers::Headers(const ::map<string, string> &headers) : m_headers(headers) {}

void Headers::set(const string &key, const string &value) {
    m_headers[key] = value;
}

const std::string &Headers::get(const string &key) const {
    auto it = m_headers.find(key);
    if (it == m_headers.end()) {
        throw invalid_argument("Header not found: " + key);
    }
    return it->second;
}

const std::map<std::string, std::string> &Headers::map() const {
    return m_headers;
}

string Headers::to_string() const {
    string raw;
    for (const auto &header : m_headers) {
        raw += header.first + ": " + header.second + "\r\n";
    }
    return raw;
}
Headers Headers::from_string(const string &raw) {
    Headers headers;
    istringstream stream(raw);
    string line;
    while (getline(stream, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1, line.size() - pos - 2);
            // +1 to skip the colon, -2 to skip the CRLF
            headers.set(key, value);
        } else {
            throw invalid_argument("Invalid header line: " + line);
        }
    }
    return headers;
}
