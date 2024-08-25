#ifndef IMPRESSHTTP_REQUEST_H
#define IMPRESSHTTP_REQUEST_H

#include <string>
#include <map>
#include "./method.h"

using namespace std;

class Request {
    string m_raw;
    Method m_method;
    string m_path;
    string m_version;
    string m_body;
    map<string, string> m_headers;
public:
    Request(string &raw, Method method, string &path, string &version, string &body, map<string, string> &headers);
    const string &raw() const;
    Method method() const;
    const string &path() const;
    const string &version() const;
    const string &body() const;
    const map<string, string> &headers() const;
    string to_string() const;
    static Request from_string(const string& request);
};


#endif//IMPRESSHTTP_REQUEST_H
