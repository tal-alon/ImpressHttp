#include "request.h"
#include <sstream>

using namespace std;

Request::Request(
        Method method,
        Path &path,
        string &version,
        string &body,
        map<string, string> &headers) : m_method(method), m_path(path), m_version(version), m_body(body), m_headers(headers) {}

Method Request::method() const { return m_method; }
const Path &Request::path() const { return m_path; }
const std::string &Request::get_query_param(const string &key) const {
    return m_path.get_param(key);
}
const string &Request::version() const { return m_version; }
const string &Request::body() const { return m_body; }
void Request::set_body(const string &body) { m_body = body; }
const map<string, string> &Request::headers() const { return m_headers; }
const std::string &Request::get_header(const string &key) const {
    return m_headers.at(key); // TODO - handle missing key
}
string Request::to_string() const {
    return method_to_string(m_method) + " " + m_path.to_string() + " " + m_version + CRLF;
}

Request Request::from_string(const string &raw) {
    Method method;
    string path_str;
    string version;
    string body;

    parse_request_line(raw, method, path_str, version);

    Path path = Path::from_string(path_str);

    auto header_start = raw.find(CRLF) + 2;
    auto header_end = raw.find(CRLF CRLF) + 2;
    string header_raw = raw.substr(header_start, header_end - header_start);
    map<string, string> headers = parse_headers(header_raw);

    return {method, path, version, body, headers};
}

// TODO - parse query params from path
void Request::parse_request_line(const string &line, Method &method, string &path, string &version) {
    istringstream stream(line);
    string method_str;

    stream >> method_str >> path >> version;
    method = str_to_method(method_str);
}

Headers Request::parse_headers(const string &raw_header) {
    Headers headers;
    istringstream stream(raw_header);
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
