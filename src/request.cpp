#include "request.h"

using namespace std;

Request::Request(
        string &raw,
        Method method,
        string &path,
        string &version,
        string &body,
        map<string, string> &headers
        ):
    m_raw(raw), m_method(method), m_path(path), m_version(version), m_body(body), m_headers(headers) {}

const string &Request::raw() const { return m_raw; }
Method Request::method() const { return m_method;}
const string &Request::path() const { return m_path; }
const string &Request::version() const { return m_version; }
const string &Request::body() const { return m_body; }
const map<string, string> &Request::headers() const { return m_headers; }
string Request::to_string() const { return m_raw; }

// TODO Implement a parser for the request string
Request Request::from_string(const string &request) {
    string raw = request;
    Method method = Method::GET;
    string path = "/";
    string version = "HTTP/1.1";
    string body = "";
    map<string, string> headers;
    return {raw, method, path, version, body, headers};
}
