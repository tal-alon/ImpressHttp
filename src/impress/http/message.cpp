#include "message.h"

#include <utility>

using namespace std;

Message::Message(string version, Headers headers, const vector<char>& body) :
    m_version(std::move(version)),
    m_headers(std::move(headers)) { set_body(body); }

Message::Message(string version, Headers headers) :
    Message(std::move(version), std::move(headers), vector<char>()) {}

Message::Message(string version, const vector<char>& body) :
    Message(std::move(version), Headers(), body) {}

Message::Message(string version) :
    Message(std::move(version), Headers(), vector<char>()) {}

const string &Message::version() const { return m_version; }
const vector<char> &Message::body() const { return m_body; }
const Headers &Message::headers() const { return m_headers; }

void Message::set_body(const vector<char> &body) {
    m_body = body;
    m_headers["Content-Length"] = to_string(body.size());
}

void Message::set_body(char *body, size_t size) {
    set_body(vector<char>(body, body + size));
}

const string *Message::get_header(const string &key) const {
    return m_headers[key];
}
