#include "headers.h"

#include <sstream>

using namespace std;

Headers::Headers() = default;

Headers::Headers(const ::map<string, string> &headers) : m_headers(headers) {}

bool Headers::has(const string &key) const {
    return m_headers.find(key) != m_headers.end();
}

std::string &Headers::operator[](const string &key) {
    return m_headers[key];
}

const std::string *Headers::operator[](const string &key) const {
    auto it = m_headers.find(key);
    if (it == m_headers.end()) {
        return nullptr;
    }
    return &it->second;
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
            headers[key] = value;
        } else {
            throw invalid_argument("Invalid header line: " + line);
        }
    }
    return headers;
}

map<string, string>::const_iterator Headers::begin() const {
    return m_headers.begin();
}

map<string, string>::const_iterator Headers::end() const {
    return m_headers.end();
}
