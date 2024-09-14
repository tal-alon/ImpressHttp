#include "request.h"
#include <sstream>
#include <utility>

using namespace std;

Request::Request(
        Method method,
        Path &path,
        string &version,
        string &body,
        Headers &headers) : m_method(std::move(method)), m_path(path), m_version(version), m_body(body), m_headers(headers) {}

Method Request::method() const { return m_method; }
const Path &Request::path() const { return m_path; }
const QueryParams &Request::query_params() const {
    return m_path.params();
}
const string &Request::version() const { return m_version; }
const string &Request::body() const { return m_body; }
void Request::set_body(const string &body) { m_body = body; }
const Headers &Request::headers() const { return m_headers; }
const std::string *Request::get_header(const string &key) const {
    return m_headers[key];
}
string Request::to_string() const {
    return m_method + " " + m_path.to_string() + " " + m_version + CRLF;
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
    Headers headers = Headers::from_string(header_raw);

    return {method, path, version, body, headers};
}

int Request::content_length() const {
    auto header = get_header("Content-Length");
    if (header == nullptr) {
        return 0;
    }
    return stoi(*header);
}

void Request::parse_request_line(const string &line, Method &method, string &path, string &version) {
    istringstream stream(line);
    stream >> method >> path >> version;
}
